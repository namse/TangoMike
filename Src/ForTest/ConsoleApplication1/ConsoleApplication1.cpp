#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "PacketType.h"


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "9001"

int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	while (1)
	{
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			continue;
		}
		
		PacketHeader * finalPacket = nullptr;

		Packet::FirstClickRequest packet0;

		Packet::VoteCompleteRequest packet1;

		Packet::SelectRequest packet2;

		Packet::ShuffleRequest packet3;

		Packet::ShowDataRequest packet4;

		Packet::HideDataRequest packet5;

		int random = rand() % 6;

		switch (random)
		{
		case 0:
			finalPacket = &packet0;
			break;

		case 1:
		{
			{
				int length = 1;//rand() % WORK_COUNT;
				packet1.objectLength = length + 1;
				packet1.object[0] = rand() % FEEL_COUNT;
				bool didUse[WORK_COUNT];
				memset(didUse, false, sizeof(didUse));
				for (int i = 1; i <= length; i++)
				{
					int randomWorkID = 0;
					do{
						randomWorkID = rand() % WORK_COUNT;
					} while (didUse[randomWorkID] != false);
					didUse[randomWorkID] = true;
					packet1.object[i] = randomWorkID + FEEL_COUNT;
				}
			}
			finalPacket = &packet1;
		}
			break;

		case 2:
		{
			int length = rand() % (WORK_COUNT + FEEL_COUNT);
			packet2.objectLength = length;
			bool didUse[WORK_COUNT + FEEL_COUNT];
			memset(didUse, false, sizeof(didUse));
			for (int i = 0; i <= length; i++)
			{
				int randomID = 0;
				do{
					randomID = rand() % (WORK_COUNT + FEEL_COUNT);
				} while (didUse[randomID] != false);
				didUse[randomID] = true;
				packet2.object[i] = randomID;
			}
		}
			finalPacket = &packet2;
			break;

		case 3:
			finalPacket = &packet3;
			break;

		case 4:
			finalPacket = &packet4;
			break;

		case 5:
			finalPacket = &packet5;
			break;

		}



		// Send an initial buffer
		iResult = send(ConnectSocket, (char*)finalPacket, (int)finalPacket->mSize, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		// cleanup
		closesocket(ConnectSocket);
		WSACleanup();
		//getchar();
	}
	return 0;
}

