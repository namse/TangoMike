#include "stdafx.h"
#include "ClientSession.h"
#include "PacketType.h"
#include "ClientManager.h"
#include "EventManager.h"
#include "Event.h"

//@{ Handler Helper

typedef void (*HandlerFunc)(ClientSession* session, PacketHeader& pktBase) ;

static HandlerFunc HandlerTable[PKT_MAX];

static void DefaultHandler(ClientSession* session, PacketHeader& pktBase)
{
	assert(false);
	session->Disconnect();
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for (int i = 0; i < PKT_MAX; ++i)
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler
{
	RegisterHandler(int pktType, HandlerFunc handler)
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(ClientSession* session, PacketHeader& pktBase); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(ClientSession* session, PacketHeader& pktBase)

//@}



bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	memcpy(&mClientAddr, addr, sizeof(SOCKADDR_IN)) ;

	/// 소켓을 넌블러킹으로 바꾸고
	u_long arg = 1 ;
	ioctlsocket(mSocket, FIONBIO, &arg) ;

	/// nagle 알고리즘 끄기
	int opt = 1 ;
	setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int)) ;

	printf("[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa(mClientAddr.sin_addr), ntohs(mClientAddr.sin_port)) ;
	
	mConnected = true ;

	return PostRecv() ;
}

bool ClientSession::PostRecv()
{
	if ( !IsConnected() )
		return false ;

	DWORD recvbytes = 0 ;
	DWORD flags = 0 ;
	WSABUF buf ;
	buf.len = (ULONG)mRecvBuffer.GetFreeSpaceSize() ;
	buf.buf = (char*)mRecvBuffer.GetBuffer() ;

	memset(&mOverlappedRecv, 0, sizeof(OverlappedIO)) ;
	mOverlappedRecv.mObject = this ;

	/// 비동기 입출력 시작
	if ( SOCKET_ERROR == WSARecv(mSocket, &buf, 1, &recvbytes, &flags, &mOverlappedRecv, RecvCompletion) )
	{
		if ( WSAGetLastError() != WSA_IO_PENDING )
			return false ;
	}

	IncOverlappedRequest() ;

	return true ;
}

void ClientSession::Disconnect()
{
	if ( !IsConnected() )
		return ;

	printf("[DEBUG] Client Disconnected: IP=%s, PORT=%d\n", inet_ntoa(mClientAddr.sin_addr), ntohs(mClientAddr.sin_port)) ;

	/// 즉각 해제

	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;

	/// no TCP TIME_WAIT
	if (SOCKET_ERROR == setsockopt(mSocket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{
		printf_s("[DEBUG] setsockopt linger option error: %d\n", GetLastError());
		return;
	}

	closesocket(mSocket) ;

	mConnected = false ;
}


void ClientSession::OnRead(size_t len)
{
	mRecvBuffer.Commit(len) ;

	/// 패킷 파싱하고 처리
	while ( true )
	{
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader header ;
		if ( false == mRecvBuffer.Peek((char*)&header, sizeof(PacketHeader)) )
			return ;

		/// 패킷 완성이 되는가? 
		if ( mRecvBuffer.GetStoredSize() < header.mSize )
			return ;

		
		if (header.mType >= PKT_MAX || header.mType <= PKT_NONE)
		{
			Disconnect();
			return;
		}

		/// packet dispatch...
		HandlerTable[header.mType](this, header);
	}
}

bool ClientSession::SendRequest(PacketHeader* pkt)
{
	if ( !IsConnected() )
		return false ;

	/// Send 요청은 버퍼에 쌓아놨다가 한번에 보낸다.
	if ( false == mSendBuffer.Write((char*)pkt, pkt->mSize) )
	{
		/// 버퍼 용량 부족인 경우는 끊어버림
		Disconnect() ;
		return false ;
	}

	return true;

}

bool ClientSession::SendFlush()
{
	if (!IsConnected())
		return false;

	/// 보낼 데이터가 없으면 그냥 리턴
	if (mSendBuffer.GetContiguiousBytes() == 0)
		return true;

	DWORD sendbytes = 0;
	DWORD flags = 0;

	WSABUF buf;
	buf.len = (ULONG)mSendBuffer.GetContiguiousBytes();
	buf.buf = (char*)mSendBuffer.GetBufferStart();

	memset(&mOverlappedSend, 0, sizeof(OverlappedIO));
	mOverlappedSend.mObject = this;

	// 비동기 입출력 시작
	if (SOCKET_ERROR == WSASend(mSocket, &buf, 1, &sendbytes, flags, &mOverlappedSend, SendCompletion))
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
			return false;
	}

	IncOverlappedRequest();

	//assert(buf.len == sendbytes);

	return true;
}

void ClientSession::OnWriteComplete(size_t len)
{
	/// 보내기 완료한 데이터는 버퍼에서 제거
	mSendBuffer.Remove(len) ;
}

bool ClientSession::Broadcast(PacketHeader* pkt)
{
	if ( !SendRequest(pkt) )
		return false ;

	if ( !IsConnected() )
		return false ;

	GClientManager->BroadcastPacket(this, pkt) ;

	return true ;
}

void ClientSession::OnTick()
{
	/// 클라별로 주기적으로 해야될 일은 여기에

}



///////////////////////////////////////////////////////////

void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject ;
	
	fromClient->DecOverlappedRequest() ;

	if ( !fromClient->IsConnected() )
		return ;

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect() ;
		return ;
	}

	/// 받은 데이터 처리
	fromClient->OnRead(cbTransferred) ;

	/// 다시 받기
	if ( false == fromClient->PostRecv() )
	{
		fromClient->Disconnect() ;
		return ;
	}
}


void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* fromClient = static_cast<OverlappedIO*>(lpOverlapped)->mObject ;

	fromClient->DecOverlappedRequest() ;

	if ( !fromClient->IsConnected() )
		return ;

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		fromClient->Disconnect() ;
		return ;
	}

	fromClient->OnWriteComplete(cbTransferred) ;

}


//////////////////////////////////////////////////////////////////

REGISTER_HANDLER(PKT_FIRST_CLICK)
{
	Packet::FirstClickRequest inPacket = static_cast<Packet::FirstClickRequest&>(pktBase);
	session->HandleFirstClickRequest(inPacket);
}
void ClientSession::HandleFirstClickRequest(Packet::FirstClickRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);
	Event::FirstClickRequest event;
	EventManager::GetInstance()->Notify(&event);
}

REGISTER_HANDLER(PKT_VOTE_COMPLETE)
{
	Packet::VoteCompleteRequest inPacket = static_cast<Packet::VoteCompleteRequest&>(pktBase);
	session->HandleVoteCompleteRequest(inPacket);
}
void ClientSession::HandleVoteCompleteRequest(Packet::VoteCompleteRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);
	/*for (int i = 0; i < inPacket.objectLength; i++)
	{
		if (inPacket.object[i] < FEEL_COUNT)
			inPacket.object[i] = FEEL_COUNT - inPacket.object[i] - 1;
	}*/
	Event::VoteCompleteRequest event;
	memcpy(&(event.objectLength),
		&(inPacket.objectLength),
		sizeof(event) - sizeof(event.event_type_));
	EventManager::GetInstance()->Notify(&event);
}

REGISTER_HANDLER(PKT_SELECT)
{
	Packet::SelectRequest inPacket = static_cast<Packet::SelectRequest&>(pktBase);
	session->HandleSelectRequest(inPacket);
}
void ClientSession::HandleSelectRequest(Packet::SelectRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);
	/*for (int i = 0; i < inPacket.objectLength; i++)
	{
		if (inPacket.object[i] < FEEL_COUNT)
			inPacket.object[i] = FEEL_COUNT - inPacket.object[i] - 1;
	}*/
	Event::SelectRequest event;
	memcpy(&(event.objectLength),
		&(inPacket.objectLength),
		sizeof(event) - sizeof(event.event_type_));
	EventManager::GetInstance()->Notify(&event);
}

REGISTER_HANDLER(PKT_SHUFFLE)
{
	Packet::ShuffleRequest inPacket = static_cast<Packet::ShuffleRequest&>(pktBase);
	session->HandleShuffleRequest(inPacket);
	
}
void ClientSession::HandleShuffleRequest(Packet::ShuffleRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);
	Event::ShuffleRequest event;
	EventManager::GetInstance()->Notify(&event);
}

REGISTER_HANDLER(PKT_SHOW_DATA)
{
	Packet::ShowDataRequest inPacket = static_cast<Packet::ShowDataRequest&>(pktBase);
	session->HandleShowDataRequest(inPacket);
}
void ClientSession::HandleShowDataRequest(Packet::ShowDataRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);

}

REGISTER_HANDLER(PKT_HIDE_DATA)
{
	Packet::HideDataRequest inPacket = static_cast<Packet::HideDataRequest&>(pktBase);
	session->HandleHideDataRequest(inPacket);
}
void ClientSession::HandleHideDataRequest(Packet::HideDataRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);

}

/*
REGISTER_HANDLER(PKT_CS_LOGIN)
{
	LoginRequest inPacket = static_cast<LoginRequest&>(pktBase) ;
	session->HandleLoginRequest(inPacket);
}

void ClientSession::HandleLoginRequest(LoginRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);

/ *
	/// 로그인은 DB 작업을 거쳐야 하기 때문에 DB 작업 요청한다.
	LoadPlayerDataContext* newDbJob = new LoadPlayerDataContext(mSocket, inPacket.mPlayerId);
	GDatabaseJobManager->PushDatabaseJobRequest(newDbJob);* /
}

REGISTER_HANDLER(PKT_CS_CHAT)
{
	ChatBroadcastRequest inPacket = static_cast<ChatBroadcastRequest&>(pktBase) ;
	session->HandleChatRequest(inPacket);
}

void ClientSession::HandleChatRequest(ChatBroadcastRequest& inPacket)
{
	mRecvBuffer.Read((char*)&inPacket, inPacket.mSize);

	ChatBroadcastResult outPacket;
	outPacket.mPlayerId = inPacket.mPlayerId;
	strcpy_s(outPacket.mName, mPlayerName);
	strcpy_s(outPacket.mChat, inPacket.mChat);

	/// 채팅은 바로 방송 하면 끝
	if (!Broadcast(&outPacket))
	{
		Disconnect();
	}
}

*/

