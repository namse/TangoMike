#pragma once
#include "stdafx.h"

#define MAX_CHAT_LEN	1024

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

enum PacketTypes
{
	PKT_NONE = -1,
	PKT_FIRST_CLICK = 0,
	PKT_VOTE_COMPLETE = 1,
	PKT_SELECT = 2,
	PKT_SHUFFLE = 3,
	PKT_SHOW_DATA = 4,
	PKT_HIDE_DATA = 5,

	PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
	short mType; 
	short mSize;
};
namespace Packet
{


	struct FirstClickRequest : public PacketHeader
	{
		FirstClickRequest()
		{
			mSize = sizeof(FirstClickRequest);
			mType = PKT_FIRST_CLICK;
		}
	};

	struct VoteCompleteRequest : public PacketHeader
	{
		VoteCompleteRequest()
		{
			mSize = sizeof(VoteCompleteRequest);
			mType = PKT_VOTE_COMPLETE;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[1 + WORK_COUNT];
	};

	struct SelectRequest : public PacketHeader
	{
		SelectRequest()
		{
			mSize = sizeof(SelectRequest);
			mType = PKT_SELECT;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[FEEL_COUNT + WORK_COUNT];
	};

	struct ShuffleRequest : public PacketHeader
	{
		ShuffleRequest()
		{
			mSize = sizeof(ShuffleRequest);
			mType = PKT_SHUFFLE;
		}
	};

	struct ShowDataRequest : public PacketHeader
	{
		ShowDataRequest()
		{
			mSize = sizeof(ShowDataRequest);
			mType = PKT_SHOW_DATA;
		}
	};

	struct HideDataRequest : public PacketHeader
	{
		HideDataRequest()
		{
			mSize = sizeof(HideDataRequest);
			mType = PKT_HIDE_DATA;
		}
	};
}
#pragma pack(pop)