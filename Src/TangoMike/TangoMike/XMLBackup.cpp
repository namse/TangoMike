#include "stdafx.h"
#include "XMLBackup.h"
#include "Relationship.h"
#include "EventManager.h"
XMLBackup* XMLBackup::pInstance_ = nullptr;

XMLBackup::XMLBackup()
{
	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);
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
		}


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

	Relationship::GetInstance()->LoadDataFromXMLBackup(&xml_doc);
}


void XMLBackup::MakeFile()
{
	pugi::xml_document doc;

	//[code_modify_add
	// add node with some name
	pugi::xml_node Communions = doc.append_child(L"Communions");

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

	doc.save_file(XML_BACKUP_NAME);
}