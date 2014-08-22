#include "stdafx.h"
#include "RightSide.h"

#define RADIUS 300.f

RightSide::RightSide()
{
	wordSpriteCollection_.InitWordSprites();
	wordSpriteCollection_.SetCenter(D2D1::Point2F(RADIUS, RADIUS));
	AddChild(&wordSpriteCollection_);

	OnArrange();
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

void RightSide::OnArrange()
{
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

		wordSprite->DoAnimate(POSITION, &(D2D1::Point2F(x, y)), 2.f);
		wordSprite->DoAnimate(ROTATION, &(wordAngle), 2.f);
		//wordSprite->SetPosition(D2D1::Point2F(x, y));
		//wordSprite->SetRotation(wordAngle);
	}
}

void RightSide::OnIdle()
{

}