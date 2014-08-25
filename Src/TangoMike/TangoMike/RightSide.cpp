#include "stdafx.h"
#include "RightSide.h"
#include "EventManager.h"
#include "Relationship.h"

RightSide::RightSide()
{
	wordSpriteCollection_.InitWordSprites();
	//wordSpriteCollection_.SetCenter(D2D1::Point2F(CIRCLE_RADIUS_TO_WORD, CIRCLE_RADIUS_TO_WORD));
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
			angle = M_PI * 2.f * 0.75f - (dAngle * (wordSprite->GetId() + 0.5f));
			wordAngle = angle - M_PI;
			float maxWidth = wordSprite->GetMaxWidth();
			x = (CIRCLE_RADIUS_TO_WORD + maxWidth) * cos(angle);
			y = (CIRCLE_RADIUS_TO_WORD + maxWidth) * sin(angle);
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);	
		}
		else
		{
			angle = M_PI * 2.f * 0.75f + (dAngle * (wordSprite->GetId() - FEEL_COUNT + 0.5f));
			wordAngle = angle;
			x = CIRCLE_RADIUS_TO_WORD * cos(angle);
			y = CIRCLE_RADIUS_TO_WORD * sin(angle);
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		}

		wordSprite->SetShuffle(false);
		wordSprite->DoAnimate(POSITION, &(D2D1::Point2F(x, y)), 2.f);
		wordSprite->SetRotation(wordAngle);
		//wordSprite->DoAnimate(ROTATION, &(wordAngle), 10.f);
	}
	/*
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		angle += dAngle;

		x = CIRCLE_RADIUS_TO_WORD * cos(angle + initAngle);
		y = CIRCLE_RADIUS_TO_WORD * sin(angle + initAngle);


		wordAngle = angle - M_PI_2;

		if (angle > M_PI)
		{
			wordAngle += M_PI;
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		}
		else
		{
			float maxWidth = wordSprite->GetMaxWidth();
			x += maxWidth * cos(angle + initAngle);
			y += maxWidth * sin(angle + initAngle);
			wordSprite->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		}

		wordSprite->SetShuffle(false);
		wordSprite->DoAnimate(POSITION, &(D2D1::Point2F(x, y)), 10.f);
		wordSprite->DoAnimate(ROTATION, &(wordAngle), 10.f);
	}*/
}

void RightSide::SetIdle()
{
	OffFocus();
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		float wordAngle = 0.f;// M_PI_2;
		wordSprite->SetShuffle(true);
		wordSprite->DoAnimate(ROTATION, &(wordAngle), 2.f);
	}
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
/*
	for (auto &SelectdObject : SelectdObjects_)
	{
		WordSprite* SelectdWordSprite = nullptr;
		for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
		{
			if (wordSprite->GetKoreanWord()->GetContents().compare(SelectdObject->GetName()) == 0)
			{
				SelectdWordSprite = wordSprite;
				break;
			}
		}
		if (SelectdWordSprite != nullptr)
		{
			SelectdWordSprite->SetFocus(true);
		}
	}*/
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

	/*for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		wordSprite->SetFocus(false);
	}*/
}
/*
	for (auto &SelectdObject : SelectdObjects_)
	{
		WordSprite* SelectdWordSprite = nullptr;
		for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
		{
			if (wordSprite->GetKoreanWord()->GetContents().compare(SelectdObject->GetName()) == 0)
			{
				SelectdWordSprite = wordSprite;
				break;
			}
		}
		if (SelectdWordSprite != nullptr)
		{
			SelectdWordSprite->SetFocus(false);
		}
	}*/
void RightSide::Notify(EventHeader* event)
{
	switch (event->event_type_)
	{
	case EVENT_FIRST_CLICK:
	{
		SetArrange();
	}break;

	case EVENT_VOTE_COMPLETE:
	{
		Event::VoteCompleteEvent* recvEvent = (Event::VoteCompleteEvent*)event;
		OffFocus();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			/*for (auto &object : Relationship::GetInstance()->GetFeels())
			{
				if (object->GetId() == recvEvent->object[i])
				{
					SelectdObjects_.push_back(object);
				}
			}
			for (auto &object : Relationship::GetInstance()->GetWorks())
			{
				if (object->GetId() == recvEvent->object[i])
				{
					SelectdObjects_.push_back(object);
				}
			}*/
			isFocus[recvEvent->object[i]] = true;
		}
		SetFocus();
	}break;

	case EVENT_SELECT:
	{
		Event::SelectEvent* recvEvent = (Event::SelectEvent*)event;
		/*SelectdObjects_.clear();
		*/
		OffFocus();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			/*for (auto &object : Relationship::GetInstance()->GetFeels())
			{
				if (object->GetId() == recvEvent->object[i])
				{
					SelectdObjects_.push_back(object);
				}
			}
			for (auto &object : Relationship::GetInstance()->GetWorks())
			{
				if (object->GetId() == recvEvent->object[i])
				{
					SelectdObjects_.push_back(object);
				}
			}*/
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