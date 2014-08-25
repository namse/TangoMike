#include "stdafx.h"
#include "Relationship.h"
#include "EventManager.h"
#include "XMLBackup.h"
Relationship* Relationship::pInstance_ = nullptr;

Relationship::Relationship() :totalUser(0)
{
	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);
	LoadMetaDataFromFile("data.txt");
	tp_feel = FindFeelById(0);
	tp_feel_count = 0;
	tp_work = FindWorkById(FEEL_COUNT + 1);
	tp_work_count = 0;
	tc_com = std::make_pair(tp_feel, tp_work);
	tc_com_count = 0;
}

void Relationship::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_VOTE_COMPLETE:
	{
		Event::SelectEvent* recvEvent = (Event::SelectEvent*)event;
		
		totalUser++;
		Event::UserCountUpdateEvent event;
		event.userCount = totalUser;
		EventManager::GetInstance()->Notify(&event);

		Feel* selectedFeel = FindFeelById(recvEvent->object[0]);
		for (int i = 1; i < recvEvent->objectLength; i++)
		{
			Work* selectedWork = FindWorkById(recvEvent->object[i]);
			if (selectedWork != nullptr)
			{
				pickCount_feel[selectedFeel]++;
				
				if (pickCount_feel[selectedFeel] >= tp_feel_count)
				{
					tp_feel_count = pickCount_feel[selectedFeel];
					tp_feel = selectedFeel;
					
					Event::TopPickFeelUpdateEvent event;
					event.tp_feel = tp_feel;
					event.tp_feel_count = tp_feel_count;
					EventManager::GetInstance()->Notify(&event);
				}
				
				
				pickCount_work[selectedWork]++;

				if (pickCount_work[selectedWork] >= tp_work_count)
				{
					tp_work_count = pickCount_work[selectedWork];
					tp_work = selectedWork;

					Event::TopPickWorkUpdateEvent event;
					event.tp_work = tp_work;
					event.tp_work_count = tp_work_count;
					EventManager::GetInstance()->Notify(&event);
				}

				auto pair = std::make_pair(selectedFeel, selectedWork);
				auto count = count_.find(pair);
				if (count_.find(pair) != count_.end())
				{
					count_.find(pair)->second++;
					if (count_.find(pair)->second > tc_com_count)
					{
						tc_com_count = count_.find(pair)->second;
						tc_com = pair;

						Event::TopCommunionUpdateEvent event;
						event.tc_com = tc_com;
						event.tc_com_count = tc_com_count;
						EventManager::GetInstance()->Notify(&event);
					}
				}
			}
		}
	}break;
	default:
		break;
	}
}

Relationship::~Relationship()
{
	for each (auto& feel in feels_)
	{
		delete feel;
	}
	for each(auto& work in works_)
	{
		delete work;
	}

	feels_.clear();
	works_.clear();
}

bool Relationship::LoadMetaDataFromFile(std::string filename)
{
	feels_.clear();
	works_.clear();

	std::wifstream ifs(filename);
	ifs.imbue(std::locale("kor"));
	if (ifs.eof())
		return false;

	int feelCount, workCount;
	std::wstring nameTemp;
	std::wstring englishNameTemp;
	float fontWidth;
	float englishFontWidth;
	ifs >> feelCount >> workCount;
	int idCount = 0;
	for (int i = 0; i < feelCount; i++)
	{
		ifs >> nameTemp >> fontWidth >> englishNameTemp >> englishFontWidth;
		feels_.push_back(new Feel(idCount++, nameTemp, fontWidth, englishNameTemp, englishFontWidth));
	}
	for (int i = 0; i < workCount; i++)
	{
		ifs >> nameTemp >> fontWidth >> englishNameTemp >> englishFontWidth;
		works_.push_back(new Work(idCount++, nameTemp, fontWidth, englishNameTemp, englishFontWidth));
	}


	// init count_
	for each (auto& feel in feels_)
	{
		for each (auto& work in works_)
		{
			count_[std::make_pair(feel, work)] = 0;
		}
	}

	return true;
}

Object* Relationship::FindObjectById(int id)
{
	for (auto& feel : feels_)
	{
		if (feel->GetId() == id)
		{
			return feel;
		}
	}
	for (auto& work : works_)
	{
		if (work->GetId() == id)
		{
			return work;
		}
	}
	return nullptr;
}

void Relationship::LoadDataFromXMLBackup(pugi::xml_document* doc)
{
	auto communions = doc->child(L"Communions");

	for (auto& feel : feels_)
	{
		for (auto& work : works_)
		{
			int count = communions.child(feel->GetNameOnXML().c_str()).child(work->GetNameOnXML().c_str()).attribute(L"CommunionCount").as_int();
			count_.find(std::make_pair(feel, work))->second = count;
		}
	}
	totalUser = doc->child(L"TotalUser").attribute(L"Count").as_int();
}
