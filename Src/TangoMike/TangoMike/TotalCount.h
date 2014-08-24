#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Word.h"
#include "WordSprite.h"
class TotalCount :
	public Component
{
public:
	TotalCount();
	~TotalCount();

	void Render();
	void Update(float dTime);

	virtual void Notify(EventHeader* event);
private:
	Word word_TotalUsers;
	Word word_TotalUsersNumber;
	
	Word word_TopPick;
	Word word_TPKorean_Feel;
	Word word_TPEnglish_Feel;
	Word word_TPCount_Feel;
	Word word_TPKorean_Work;
	Word word_TPEnglish_Work;
	Word word_TPCount_Work;

	Word word_TopComunion;
	Word word_TCKorean_Feel;
	Word word_TCKorean_Work;
	Word word_TCEnglish_Feel;
	Word word_TCEnglish_Work;
	Word word_TCCount;
};

