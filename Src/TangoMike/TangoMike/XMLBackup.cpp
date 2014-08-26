#include "stdafx.h"
#include "XMLBackup.h"
#include "Relationship.h"
#include "EventManager.h"
XMLBackup* XMLBackup::pInstance_ = nullptr;

XMLBackup::XMLBackup()
{
	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_FEEL_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_WORK_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_COMMUNION_UPDATE, this);
}


XMLBackup::~XMLBackup()
{
}

void XMLBackup::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_VOTE_COMPLETE:
	{
		Event::SelectEvent* recvEvent = (Event::SelectEvent*)event;

		xml_doc.child(L"TotalUser").attribute(L"Count") = xml_doc.child(L"TotalUser").attribute(L"Count").as_int() + 1;

		Feel* selectedFeel = Relationship::GetInstance()->FindFeelById(recvEvent->object[0]);
		auto feel_node = xml_doc.child(L"Communions").child(selectedFeel->GetNameOnXML().c_str());
		for (int i = 1; i < recvEvent->objectLength; i++)
		{
			Work* selectedWork = Relationship::GetInstance()->FindWorkById(recvEvent->object[i]);
			if (selectedWork != nullptr)
			{
				auto work_node = feel_node.child(selectedWork->GetNameOnXML().c_str());
				work_node.attribute(L"CommunionCount") = work_node.attribute(L"CommunionCount").as_int() + 1;
			}
			int index = xml_doc.child(L"RecentLines").attribute(L"Index").as_int();
			std::wstring str = L"_";
			str += std::to_wstring(index);
			auto line = xml_doc.child(L"RecentLines").child(str.c_str());
			line.attribute(L"Feel") = recvEvent->object[0];
			line.attribute(L"Work") = recvEvent->object[i];
			index = (index + 1) % MAX_LINE_COUNT;
			xml_doc.child(L"RecentLines").attribute(L"Index").set_value(index);
		}

		xml_doc.save_file(XML_BACKUP_NAME);
	}break;

	case EVENT_TOP_PICK_FEEL_UPDATE:
	{
		Event::TopPickFeelUpdateEvent *recvEvent = (Event::TopPickFeelUpdateEvent*)event;
		xml_doc.child(L"Communions").attribute(L"TP_Feel") = recvEvent->tp_feel->GetId();
		xml_doc.child(L"Communions").attribute(L"TP_Feel_Count") = recvEvent->tp_feel_count;
		xml_doc.save_file(XML_BACKUP_NAME);
	}break;


	case EVENT_TOP_PICK_WORK_UPDATE:
	{
		Event::TopPickWorkUpdateEvent *recvEvent = (Event::TopPickWorkUpdateEvent*)event;
		xml_doc.child(L"Communions").attribute(L"TP_Work") = recvEvent->tp_work->GetId();
		xml_doc.child(L"Communions").attribute(L"TP_Work_Count") = recvEvent->tp_work_count;
		xml_doc.save_file(XML_BACKUP_NAME);
	}break;


	case EVENT_TOP_COMMUNION_UPDATE:
	{
		Event::TopCommunionUpdateEvent *recvEvent = (Event::TopCommunionUpdateEvent*)event;
		xml_doc.child(L"Communions").attribute(L"TC_Feel") = recvEvent->tc_com.first->GetId();
		xml_doc.child(L"Communions").attribute(L"TC_Work") = recvEvent->tc_com.second->GetId();
		xml_doc.child(L"Communions").attribute(L"TC_Count") = recvEvent->tc_com_count;
		xml_doc.save_file(XML_BACKUP_NAME);
	}break;
	}
}
void XMLBackup::LoadData()
{
	if (IsFileExist(XML_BACKUP_NAME) == false)
	{
		MakeFile();
	}

	
	pugi::xml_parse_result result = xml_doc.load_file(XML_BACKUP_NAME);

	if (!result)
	{
		MakeFile();

		pugi::xml_parse_result result = xml_doc.load_file(XML_BACKUP_NAME);
		if (!result)
		{
			std::cout << "wrong file, " << result.description() << std::endl;
		}
	}
	
}


void XMLBackup::MakeFile()
{
	pugi::xml_document doc;

	//[code_modify_add
	// add node with some name
	pugi::xml_node Communions = doc.append_child(L"Communions");
	Communions.append_attribute(L"TP_Feel") = 0;
	Communions.append_attribute(L"TP_Feel_Count") = 0;
	Communions.append_attribute(L"TP_Work") = FEEL_COUNT;
	Communions.append_attribute(L"TP_Work_Count") = 0;
	Communions.append_attribute(L"TC_Feel") = 0;
	Communions.append_attribute(L"TC_Work") = FEEL_COUNT;
	Communions.append_attribute(L"TC_Count") = 0;

	for (Feel* feel : Relationship::GetInstance()->GetFeels())
	{
		pugi::xml_node feel_node = Communions.append_child(feel->GetNameOnXML().c_str());
		for (Work* work : Relationship::GetInstance()->GetWorks())
		{
			pugi::xml_node work_node = feel_node.append_child(work->GetNameOnXML().c_str());
			work_node.append_attribute(L"CommunionCount") = Relationship::GetInstance()->GetCount(feel, work);
		}
	}

	doc.append_child(L"TotalUser").append_attribute(L"Count") = Relationship::GetInstance()->GetTotalUserCount();

	auto recentLines = doc.append_child(L"RecentLines");
	recentLines.append_attribute(L"Index") = 0;
	for (int i = 0; i < MAX_LINE_COUNT; i++)
	{
		std::wstring str = L"_";
		str += std::to_wstring(i);
		auto line = recentLines.append_child(str.c_str());
		line.append_attribute(L"Feel") = -1;
		line.append_attribute(L"Work") = -1;
	}

	doc.save_file(XML_BACKUP_NAME);
}

std::list<std::pair<int, int>> XMLBackup::LoadLines()
{
	std::list<std::pair<int, int>> ret;
	auto recentLines = xml_doc.child(L"RecentLines");
	for (int i = 0; i < MAX_LINE_COUNT; i++)
	{
		std::wstring str = L"_";
		str += std::to_wstring(i);
		auto line = recentLines.child(str.c_str());
		int feel = line.attribute(L"Feel").as_int();
		int work = line.attribute(L"Work").as_int();

		if (feel != -1 && work != -1)
		{
			ret.push_back(std::make_pair(feel, work));
		}
	}
	return ret;
}
