#include "stdafx.h"
#include "TotalCount.h"
#include "Relationship.h"
#include "EventManager.h"
TotalCount::TotalCount()
	: word_TotalUsers(TOTAL_COUNT_CONTENTS_TOTAL_USERS, TOTAL_COUNT_POSITION_TOTAL_USERS)
	, word_TotalUsersNumber(L"", TOTAL_COUNT_POSITION_TOTAL_USERS_NUMBER)
	, word_TopPick(TOTAL_COUNT_CONTENTS_TOP_PICKS, TOTAL_COUNT_POSITION_TOP_PICK)
	, word_TPKorean_Feel(L"", TOTAL_COUNT_POSITION_TP_KOREAN_FEEL)
	, word_TPEnglish_Feel(L"", TOTAL_COUNT_POSITION_TP_ENGLISH_FEEL)
	, word_TPCount_Feel(L"", TOTAL_COUNT_POSITION_TP_COUNT_FEEL)
	, word_TPKorean_Work(L"", TOTAL_COUNT_POSITION_TP_KOREAN_WORK)
	, word_TPEnglish_Work(L"", TOTAL_COUNT_POSITION_TP_ENGLISH_WORK)
	, word_TPCount_Work(L"", TOTAL_COUNT_POSITION_TP_COUNT_WORK)
	, word_TopComunion(TOTAL_COUNT_CONTENTS_TOP_COMMUNION, TOTAL_COUNT_POSITION_TOP_COMMUNION)
	, word_TCKorean_Feel(L"", TOTAL_COUNT_POSITION_TC_KOREAN_FEEL)
	, word_TCKorean_Work(L"", TOTAL_COUNT_POSITION_TC_KOREAN_WORK)
	, word_TCEnglish_Feel(L"", TOTAL_COUNT_POSITION_TC_ENGLISH_FEEL)
	, word_TCEnglish_Work(L"", TOTAL_COUNT_POSITION_TC_ENGLISH_WORK)
	, word_TCCount(L"", TOTAL_COUNT_POSITION_TC_COUNT)
{
	word_TotalUsers.SetFontSize(TOTAL_COUNT_FONTSIZE_TITLE);
	word_TotalUsersNumber.SetFontSize(TOTAL_COUNT_FONTSIZE_TU_COUNT);
	word_TopPick.SetFontSize(TOTAL_COUNT_FONTSIZE_TITLE);
	word_TPKorean_Feel.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_KOREAN);
	word_TPEnglish_Feel.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_ENGLSIH);
	word_TPCount_Feel.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_COUNT);
	word_TPKorean_Work.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_KOREAN);
	word_TPEnglish_Work.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_ENGLSIH);
	word_TPCount_Work.SetFontSize(TOTAL_COUNT_FONTSIZE_TP_COUNT);
	word_TopComunion.SetFontSize(TOTAL_COUNT_FONTSIZE_TITLE);
	word_TCKorean_Feel.SetFontSize(TOTAL_COUNT_FONTSIZE_TC_KOREAN);
	word_TCKorean_Work.SetFontSize(TOTAL_COUNT_FONTSIZE_TC_KOREAN);
	word_TCEnglish_Feel.SetFontSize(TOTAL_COUNT_FONTSIZE_TC_ENGLISH);
	word_TCEnglish_Work.SetFontSize(TOTAL_COUNT_FONTSIZE_TC_ENGLISH);
	word_TCCount.SetFontSize(TOTAL_COUNT_FONTSIZE_TC_COUNT);


	word_TotalUsers.SetFontColor(TOTAL_COUNT_FONTCOLOR_TITLE);
	word_TotalUsersNumber.SetFontColor(TOTAL_COUNT_FONTCOLOR_COUNT);
	word_TopPick.SetFontColor(TOTAL_COUNT_FONTCOLOR_TITLE);
	word_TPKorean_Feel.SetFontColor(FONTCOLOR_FEEL_FOCUS);
	word_TPEnglish_Feel.SetFontColor(FONTCOLOR_FEEL_FOCUS);
	word_TPCount_Feel.SetFontColor(FONTCOLOR_FEEL_FOCUS);
	word_TPKorean_Work.SetFontColor(FONTCOLOR_WORK_FOCUS);
	word_TPEnglish_Work.SetFontColor(FONTCOLOR_WORK_FOCUS);
	word_TPCount_Work.SetFontColor(FONTCOLOR_WORK_FOCUS);
	word_TopComunion.SetFontColor(TOTAL_COUNT_FONTCOLOR_TITLE);
	word_TCKorean_Feel.SetFontColor(FONTCOLOR_FEEL_FOCUS);
	word_TCKorean_Work.SetFontColor(FONTCOLOR_WORK_FOCUS);
	word_TCEnglish_Feel.SetFontColor(FONTCOLOR_FEEL_FOCUS);
	word_TCEnglish_Work.SetFontColor(FONTCOLOR_WORK_FOCUS);
	word_TCCount.SetFontColor(TOTAL_COUNT_FONTCOLOR_COUNT);

	word_TotalUsers.SetFontName(TOTAL_COUNT_FONTNAME_TITLE);
	word_TotalUsersNumber.SetFontName(TOTAL_COUNT_FONTNAME_COUNT);
	word_TopPick.SetFontName(TOTAL_COUNT_FONTNAME_TITLE);
	word_TPKorean_Feel.SetFontName(TOTAL_COUNT_FONTNAME_KOREAN);
	word_TPEnglish_Feel.SetFontName(TOTAL_COUNT_FONTNAME_ENGLSIH);
	word_TPCount_Feel.SetFontName(TOTAL_COUNT_FONTNAME_COUNT);
	word_TPKorean_Work.SetFontName(TOTAL_COUNT_FONTNAME_KOREAN);
	word_TPEnglish_Work.SetFontName(TOTAL_COUNT_FONTNAME_ENGLSIH);
	word_TPCount_Work.SetFontName(TOTAL_COUNT_FONTNAME_COUNT);
	word_TopComunion.SetFontName(TOTAL_COUNT_FONTNAME_TITLE);
	word_TCKorean_Feel.SetFontName(TOTAL_COUNT_FONTNAME_KOREAN);
	word_TCKorean_Work.SetFontName(TOTAL_COUNT_FONTNAME_KOREAN);
	word_TCEnglish_Feel.SetFontName(TOTAL_COUNT_FONTNAME_ENGLSIH);
	word_TCEnglish_Work.SetFontName(TOTAL_COUNT_FONTNAME_ENGLSIH);
	word_TCCount.SetFontName(TOTAL_COUNT_FONTNAME_COUNT);



	AddChild(&word_TotalUsers);
	AddChild(&word_TotalUsersNumber);

	AddChild(&word_TopPick);
	AddChild(&word_TPKorean_Feel);
	AddChild(&word_TPEnglish_Feel);
	AddChild(&word_TPCount_Feel);
	AddChild(&word_TPKorean_Work);
	AddChild(&word_TPEnglish_Work);
	AddChild(&word_TPCount_Work);

	AddChild(&word_TopComunion);
	AddChild(&word_TCKorean_Feel);
	AddChild(&word_TCKorean_Work);
	AddChild(&word_TCEnglish_Feel);
	AddChild(&word_TCEnglish_Work);
	AddChild(&word_TCCount);

	for (auto& child : childs_)
	{
		Word* word = (Word*)child;
		word->SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));
	}

	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_WORK_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_FEEL_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_COMMUNION_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_USER_COUNT_UPDATE, this);
}

TotalCount::~TotalCount()
{
}

void TotalCount::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_TOP_PICK_FEEL_UPDATE:
	{
		Event::TopPickFeelUpdateEvent* recvEvent = (Event::TopPickFeelUpdateEvent*) event;
		word_TPKorean_Feel.SetContents(recvEvent->tp_feel->GetName());
		word_TPEnglish_Feel.SetContents(recvEvent->tp_feel->GetEnglishName());
		word_TPCount_Feel.SetContents(std::to_wstring (recvEvent->tp_feel_count));
	}break;
	case EVENT_TOP_PICK_WORK_UPDATE:
	{
		Event::TopPickWorkUpdateEvent* recvEvent = (Event::TopPickWorkUpdateEvent*) event;
		word_TPKorean_Work.SetContents(recvEvent->tp_work->GetName());
		word_TPEnglish_Work.SetContents(recvEvent->tp_work->GetEnglishName());
		word_TPCount_Work.SetContents(std::to_wstring(recvEvent->tp_work_count));
	}break;
	case EVENT_TOP_COMMUNION_UPDATE:
	{
		Event::TopCommunionUpdateEvent* recvEvent = (Event::TopCommunionUpdateEvent*) event;
		word_TCKorean_Feel.SetContents(recvEvent->tc_com.first->GetName());
		word_TCEnglish_Feel.SetContents(recvEvent->tc_com.first->GetEnglishName());
		word_TCKorean_Work.SetContents(recvEvent->tc_com.second->GetName());
		word_TCEnglish_Work.SetContents(recvEvent->tc_com.second->GetEnglishName());
		word_TCCount.SetContents(std::to_wstring(recvEvent->tc_com_count));
	}break;
	case EVENT_USER_COUNT_UPDATE:
	{
		Event::UserCountUpdateEvent* recvEvent = (Event::UserCountUpdateEvent*) event;
		word_TotalUsersNumber.SetContents(std::to_wstring(recvEvent->userCount));
	}break;
	}
}

void TotalCount::Render()
{
	Component::Render();
}

void TotalCount::Update(float dTime)
{
	Component::Update(dTime);

}
