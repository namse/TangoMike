#pragma once
#include <memory>
enum EventTypes
{
	EVENT_NONE = -1,
	EVENT_FIRST_CLICK = 0,
	EVENT_VOTE_COMPLETE = 1,
	EVENT_SELECT = 2,
	EVENT_SHUFFLE = 3,
	EVENT_SHOW_DATA = 4,
	EVENT_HIDE_DATA = 5,

} ;

struct EventHeader
{
	EventTypes event_type_;
};

namespace Event
{
	struct FirstClickRequest : public EventHeader
	{
		FirstClickRequest()
		{
			event_type_ = EVENT_FIRST_CLICK;
		}
	};

	struct VoteCompleteRequest : public EventHeader
	{
		VoteCompleteRequest()
		{
			event_type_ = EVENT_VOTE_COMPLETE;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[1 + WORK_COUNT];
	};

	struct SelectRequest : public EventHeader
	{
		SelectRequest()
		{
			event_type_ = EVENT_SELECT;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[FEEL_COUNT + WORK_COUNT];
	};

	struct ShuffleRequest : public EventHeader
	{
		ShuffleRequest()
		{
			event_type_ = EVENT_SHUFFLE;
		}
	};

	struct ShowDataRequest : public EventHeader
	{
		ShowDataRequest()
		{
			event_type_ = EVENT_SHOW_DATA;
		}
	};

	struct HideDataRequest : public EventHeader
	{
		HideDataRequest()
		{
			event_type_ = EVENT_HIDE_DATA;
		}
	};
}