#include "stdafx.h"
#include "RightSide.h"
#include "EventManager.h"
#include "Relationship.h"

RightSide::RightSide()
	: isIdle(false), TimeForIdle(0.f)
{
	wordSpriteCollection_.InitWordSprites();
	SetPosition(CIRCLE_CENTER_POSITION);
	AddChild(&wordSpriteCollection_);
	AddChild(&lineCollection_);

	SetArrange();

	EventManager::GetInstance()->AddEventListener(EVENT_FIRST_CLICK, this);
	EventManager::GetInstance()->AddEventListener(EVENT_VOTE_COMPLETE, this);
	EventManager::GetInstance()->AddEventListener(EVENT_SELECT, this);
	EventManager::GetInstance()->AddEventListener(EVENT_SHUFFLE, this);
	
}


RightSide::~RightSide()
{
	
}

void RightSide::Render()
{
	Component::Render();
}


void RightSide::Update(float dTime)
{
	Component::Update(dTime);

	if (isIdle == true)
	{
		TimeForIdle += dTime;
		if (TimeForIdle > SHUFFLE_PERIOD)
		{
			TimeForIdle = 0.f;
			Event::SelectEvent event;
			int length = rand() % (WORK_COUNT + FEEL_COUNT);
			event.objectLength = length;
			bool didUse[WORK_COUNT + FEEL_COUNT];
			memset(didUse, false, sizeof(didUse));
			for (int i = 0; i <= length; i++)
			{
				int randomID = 0;
				do{
					randomID = rand() % (WORK_COUNT + FEEL_COUNT);
				} while (didUse[randomID] != false);
				didUse[randomID] = true;
				event.object[i] = randomID;
			}
			EventManager::GetInstance()->Notify(&event);
		}
	}
}

void RightSide::SetArrange()
{
	OffFocus();
	float angle = 0.f;
	float initAngle = M_PI_2;
	float dAngle = M_PI * 2.f / wordSpriteCollection_.GetWordSprites().size();
	float wordAngle;
	

	float x, y;
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{

		x = CIRCLE_RADIUS_TO_WORD * cos(angle + initAngle);
		y = CIRCLE_RADIUS_TO_WORD * sin(angle + initAngle);
		

		if (wordSprite->IsFeel())
		{
			angle = M_PI * 2.f * 0.75f - (dAngle * (wordSprite->GetId()));
			wordAngle = angle - M_PI;
			float maxWidth = wordSprite->GetMaxWidth();
			x = (CIRCLE_RADIUS_TO_WORD + maxWidth) * cos(angle);
			y = (CIRCLE_RADIUS_TO_WORD + maxWidth) * sin(angle);
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);	
		}
		else
		{
			angle = M_PI * 2.f * 0.75f + (dAngle * (wordSprite->GetId() - FEEL_COUNT + 1.f));
			wordAngle = angle;
			x = CIRCLE_RADIUS_TO_WORD * cos(angle);
			y = CIRCLE_RADIUS_TO_WORD * sin(angle);
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		}

		wordSprite->SetShuffle(false);
		wordSprite->DoAnimate(POSITION, &(D2D1::Point2F(x, y)), 2.f);
		wordSprite->SetRotation(wordAngle);
	}
}

void RightSide::SetIdle()
{
	isIdle = true;
}


void RightSide::SetFocus()
{
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		if (isFocus[wordSprite->GetId()] == true)
		{
			wordSprite->SetFocus(true);
		}
	}
}


void RightSide::OffFocus()
{
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		if (isFocus[wordSprite->GetId()] == true)
		{
			wordSprite->SetFocus(false);
		}
	}
	memset(isFocus, false, sizeof(isFocus));
}

void RightSide::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_FIRST_CLICK:
	{
		OffShuffle();
		OffFocus();
		SetArrange();
	}break;

	case EVENT_VOTE_COMPLETE:
	{
		OffShuffle();
		Event::VoteCompleteEvent* recvEvent = (Event::VoteCompleteEvent*)event;
		OffFocus();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			isFocus[recvEvent->object[i]] = true;
		}
		SetFocus();
	}break;

	case EVENT_SELECT:
	{
		OffShuffle();
		Event::SelectEvent* recvEvent = (Event::SelectEvent*)event;
		OffFocus();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			isFocus[recvEvent->object[i]] = true;
		}
		SetFocus();
	}break;

	case EVENT_SHUFFLE:
	{
		Event::ShuffleEvent* recvEvent = (Event::ShuffleEvent*)event;
		SetIdle();
	}break;

	default:
	{
		break;
	}
	}
}

void RightSide::OffShuffle()
{
	isIdle = false;
	TimeForIdle = 0.f;
}
