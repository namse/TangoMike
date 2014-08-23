#include "stdafx.h"
#include "RightSide.h"
#include "EventManager.h"
#include "Relationship.h"
#define RADIUS 300.f

RightSide::RightSide()
{
	wordSpriteCollection_.InitWordSprites();
	wordSpriteCollection_.SetCenter(D2D1::Point2F(RADIUS, RADIUS));
	AddChild(&wordSpriteCollection_);

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
	angle = dAngle / 2.f;
	

	float x, y;

	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		angle += dAngle;

		x = RADIUS * cos(angle + initAngle);
		y = RADIUS * sin(angle + initAngle);
		

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
		//wordSprite->SetPosition(D2D1::Point2F(x, y));
		//wordSprite->SetRotation(wordAngle);
	}
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
	}
}

void RightSide::OffFocus()
{
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		wordSprite->SetFocus(false);
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
		Event::VoteCompleteRequest* recvEvent = (Event::VoteCompleteRequest*)event;
		SelectdObjects_.clear();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			for (auto &object : Relationship::GetInstance()->GetFeels())
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
			}
		}
	}break;

	case EVENT_SELECT:
	{
		Event::SelectRequest* recvEvent = (Event::SelectRequest*)event;
		SelectdObjects_.clear();
		for (int i = 0; i < recvEvent->objectLength; i++)
		{
			for (auto &object : Relationship::GetInstance()->GetFeels())
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
			}
		}
	}break;

	case EVENT_SHUFFLE:
	{
		Event::ShuffleRequest* recvEvent = (Event::ShuffleRequest*)event;
		SetIdle();
	}break;

	default:
	{
		break;
	}
	}
}