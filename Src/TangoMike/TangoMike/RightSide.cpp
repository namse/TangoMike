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
	angle = -dAngle/4.f;
	

	float x, y;
	for (auto &wordSprite : wordSpriteCollection_.GetWordSprites())
	{
		angle += dAngle;

		x = CIRCLE_RADIUS_TO_WORD * cos(angle + initAngle);
		y = CIRCLE_RADIUS_TO_WORD * sin(angle + initAngle);
		

		wordAngle = angle - M_PI_2;

		if (wordSprite->IsWork())
		{
			wordAngle += M_PI;
			x = CIRCLE_RADIUS_TO_WORD * cos(angle + initAngle - dAngle/2.f);
			y = CIRCLE_RADIUS_TO_WORD * sin(angle + initAngle - dAngle/2.f);
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
		SetFocus();
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
		SetFocus();
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