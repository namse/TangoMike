#include "stdafx.h"
#include "Relationship.h"
#include "EventManager.h"
Relationship* Relationship::pInstance_ = nullptr;

Relationship::Relationship() :totalUser(0)
{
	EventManager::GetInstance()->AddEventListener(EVENT_SELECT, this);
}

void Relationship::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_VOTE_COMPLETE:
	{
		Event::SelectRequest* recvEvent = (Event::SelectRequest*)event;

		Feel* selectedFeel = FindFeelById(recvEvent->object[0]);
		for (int i = 1; i < recvEvent->objectLength; i++)
		{
			Work* selectedWork = FindWorkById(recvEvent->object[i]);
			if (selectedWork != nullptr)
			{
				auto count = count_.find(std::make_pair(selectedFeel, selectedWork));
				if (count_.find(std::make_pair(selectedFeel, selectedWork)) != count_.end())
				{
					std::cout << count_.find(std::make_pair(selectedFeel, selectedWork))->second;
					count_.find(std::make_pair(selectedFeel, selectedWork))->second++;
					std::cout << count_.find(std::make_pair(selectedFeel, selectedWork))->second;
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

bool Relationship::LoadDataFromFile(std::string filename)
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
