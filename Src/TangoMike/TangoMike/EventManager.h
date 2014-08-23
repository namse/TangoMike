#pragma once
#include "Event.h"
#include "EventListener.h"
#include <map>
class EventManager
{
public:
	EventManager(void);
	~EventManager(void);

	void AddEventListener(EventTypes event_type, EventListener* listener);
	void RemoveEventListener(EventTypes event_type, EventListener* listener);
	void RemoveEventListener(EventListener* listener);
	void Notify(EventHeader* event);



private:
	std::multimap<EventTypes, EventListener*> event_listener_list;

};


extern EventManager* g_event_manager;