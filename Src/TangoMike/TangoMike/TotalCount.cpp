#include "stdafx.h"
#include "TotalCount.h"
#include "Relationship.h"

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
	, word_TopComunion(TOTAL_COUNT_CONTENTS_TOP_COMMUNION, TOTAL_COUNT_POSITION_TC_COUNT)
	, word_TCKorean_Feel(L"", TOTAL_COUNT_POSITION_TP_KOREAN_FEEL)
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
}


TotalCount::~TotalCount()
{
}

void TotalCount::Render()
{
	Component::Render();
}

void TotalCount::Update(float dTime)
{
	Component::Update(dTime);

	//TODO : Update Contents with relationship.
}
