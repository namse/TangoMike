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
	, animatingWordGroup()
	, tpFCount(0), tpWCount(0), tcCount(0), opacity(0.f)
	, tpFCount_ani(0), tpWCount_ani(0), tcCount_ani(0)
	, opacityAnimation(&opacity)
	, tpFeelCountAnimation(&tpFCount_ani)
	, tpWorkCountAnimation(&tpWCount_ani)
	, tcCountAnimation(&tcCount_ani)
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

	animatingWordGroup.SetPosition(D2D1::Point2F(0.f, +25.f));
	animatingWordGroup.AddChild(&word_TopPick);
	animatingWordGroup.AddChild(&word_TPKorean_Feel);
	animatingWordGroup.AddChild(&word_TPEnglish_Feel);
	animatingWordGroup.AddChild(&word_TPCount_Feel);
	animatingWordGroup.AddChild(&word_TPKorean_Work);
	animatingWordGroup.AddChild(&word_TPEnglish_Work);
	animatingWordGroup.AddChild(&word_TPCount_Work);

	animatingWordGroup.AddChild(&word_TopComunion);
	animatingWordGroup.AddChild(&word_TCKorean_Feel);
	animatingWordGroup.AddChild(&word_TCKorean_Work);
	animatingWordGroup.AddChild(&word_TCEnglish_Feel);
	animatingWordGroup.AddChild(&word_TCEnglish_Work);
	animatingWordGroup.AddChild(&word_TCCount);

	AddChild(&animatingWordGroup);

	for (auto& child : childs_)
	{
		Word* word = (Word*)child;
		word->SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));
	}
	for (auto& child : animatingWordGroup.GetChildern())
	{
		Word* word = (Word*)child;
		word->SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));

		originPosition.push_back(*word->GetPosition());
	}

	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_WORK_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_PICK_FEEL_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_TOP_COMMUNION_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_USER_COUNT_UPDATE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_SHOW_DATA, this);
	EventManager::GetInstance()->AddEventListener(EVENT_HIDE_DATA, this);
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
		tpFCount = recvEvent->tp_feel_count;
		//word_TPCount_Feel.SetContents(std::to_wstring (recvEvent->tp_feel_count));
	}break;
	case EVENT_TOP_PICK_WORK_UPDATE:
	{
		Event::TopPickWorkUpdateEvent* recvEvent = (Event::TopPickWorkUpdateEvent*) event;
		word_TPKorean_Work.SetContents(recvEvent->tp_work->GetName());
		word_TPEnglish_Work.SetContents(recvEvent->tp_work->GetEnglishName());
		tpWCount = recvEvent->tp_work_count;
		//word_TPCount_Work.SetContents(std::to_wstring(recvEvent->tp_work_count));
	}break;
	case EVENT_TOP_COMMUNION_UPDATE:
	{
		Event::TopCommunionUpdateEvent* recvEvent = (Event::TopCommunionUpdateEvent*) event;
		word_TCKorean_Feel.SetContents(recvEvent->tc_com.first->GetName());
		word_TCEnglish_Feel.SetContents(recvEvent->tc_com.first->GetEnglishName());
		word_TCKorean_Work.SetContents(recvEvent->tc_com.second->GetName());
		word_TCEnglish_Work.SetContents(recvEvent->tc_com.second->GetEnglishName());
		tcCount = recvEvent->tc_com_count;
		//word_TCCount.SetContents(std::to_wstring(recvEvent->tc_com_count));
	}break;
	case EVENT_USER_COUNT_UPDATE:
	{
		Event::UserCountUpdateEvent* recvEvent = (Event::UserCountUpdateEvent*) event;
		word_TotalUsersNumber.SetContents(std::to_wstring(recvEvent->userCount));
	}break;
	case EVENT_SHOW_DATA:
	{
		// Start Animation
		opacity = 0.f;
		tpFCount_ani = 0;
		tpWCount_ani = 0;
		tcCount_ani = 0;
		opacityAnimation.DoAnimate(1.f, 1.f);
		tpFeelCountAnimation.DoAnimate(tpFCount, 2.f);
		tpWorkCountAnimation.DoAnimate(tpWCount, 2.f);
		tcCountAnimation.DoAnimate(tcCount, 2.f);

	}break;
	case EVENT_HIDE_DATA:
	{
		// Fade Off this.
		opacityAnimation.DoAnimate(0.f, 1.f);
	}break;
	}
}

void TotalCount::Render()
{
	word_TPCount_Feel.SetContents(std::to_wstring(tpFCount_ani));
	word_TPCount_Work.SetContents(std::to_wstring(tpWCount_ani));
	word_TCCount.SetContents(std::to_wstring(tcCount_ani));

	int i = 0;
	for (auto& child : animatingWordGroup.GetChildern())
	{
		Word* word = (Word*)child;
		auto fontcolor = word->Getfontcolor();
		fontcolor.a = opacity;
		word->SetFontColor(fontcolor);

		word->SetPosition(originPosition[i] + D2D1::Point2F(0.f, - opacity * 25.f));

		i++;
	}


	Component::Render();


}

void TotalCount::Update(float dTime)
{
	Component::Update(dTime);

	opacityAnimation.OnAnimate(dTime);
	tpFeelCountAnimation.OnAnimate(dTime);
	tpWorkCountAnimation.OnAnimate(dTime);
	tcCountAnimation.OnAnimate(dTime);

	//std::cout << animatingWordGroup.GetPosition()->x << " " << animatingWordGroup.GetPosition()->y << " " << tpWCount_ani << " " << tcCount_ani
	//	<<" "<< (word_TCKorean_Work.GetPosition()->y) - (word_TCCount.GetPosition()->y) << " " << word_TCKorean_Work.GetPosition()->y << " " << std::endl;

}
