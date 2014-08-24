#pragma once
#include <memory>
#include "Feel.h"
#include "Work.h"
enum EventTypes
{
	EVENT_NONE = -1,
	EVENT_FIRST_CLICK = 0,
	EVENT_VOTE_COMPLETE = 1,
	EVENT_SELECT = 2,
	EVENT_SHUFFLE = 3,
	EVENT_SHOW_DATA = 4,
	EVENT_HIDE_DATA = 5,

	EVENT_TOP_PICK_FEEL_UPDATE = 6,
	EVENT_TOP_PICK_WORK_UPDATE = 7,
	EVENT_TOP_COMMUNION_UPDATE = 8,
	EVENT_USER_COUNT_UPDATE = 9,

} ;

struct EventHeader
{
	EventTypes event_type_;
};

namespace Event
{
	struct FirstClickEvent : public EventHeader
	{
		FirstClickEvent()
		{
			event_type_ = EVENT_FIRST_CLICK;
		}
	};

	struct VoteCompleteEvent : public EventHeader
	{
		VoteCompleteEvent()
		{
			event_type_ = EVENT_VOTE_COMPLETE;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[1 + WORK_COUNT];
	};

	struct SelectEvent : public EventHeader
	{
		SelectEvent()
		{
			event_type_ = EVENT_SELECT;
			objectLength = 0;
			memset(object, -1, sizeof(object));
		}
		char objectLength;
		char object[FEEL_COUNT + WORK_COUNT];
	};

	struct ShuffleEvent : public EventHeader
	{
		ShuffleEvent()
		{
			event_type_ = EVENT_SHUFFLE;
		}
	};

	struct ShowDataEvent : public EventHeader
	{
		ShowDataEvent()
		{
			event_type_ = EVENT_SHOW_DATA;
		}
	};

	struct HideDataEvent : public EventHeader
	{
		HideDataEvent()
		{
			event_type_ = EVENT_HIDE_DATA;
		}
	};

	struct TopPickFeelUpdateEvent : public EventHeader
	{
		TopPickFeelUpdateEvent()
		{
			event_type_ = EVENT_TOP_PICK_FEEL_UPDATE;
		}
		Feel* tp_feel;
		int tp_feel_count;
	};

	struct TopPickWorkUpdateEvent : public EventHeader
	{
		TopPickWorkUpdateEvent()
		{
			event_type_ = EVENT_TOP_PICK_WORK_UPDATE;
		}
		Work* tp_work;
		int tp_work_count;
	};

	struct TopCommunionUpdateEvent : public EventHeader
	{
		TopCommunionUpdateEvent()
		{
			event_type_ = EVENT_TOP_COMMUNION_UPDATE;
		}
		std::pair<Feel*, Work*> tc_com;
		int tc_com_count;
	};

	struct UserCountUpdateEvent : public EventHeader
	{
		UserCountUpdateEvent()
		{
			event_type_ = EVENT_USER_COUNT_UPDATE;
		}
		int userCount;
	};
}