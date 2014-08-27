#include "stdafx.h"
#include "WordSprite.h"
#include "Relationship.h"



WordSprite::WordSprite(Object& object)
{
	float maxWidth = max(object.GetWidth(), object.GetEnglishWidth());

	koreanWord_.SetContents(object.GetName());
	koreanWord_.SetFontSize(KOREAN_IDLE_FONT_SIZE);
	koreanWord_.SetPosition(D2D1::Point2F(0.f, 0.f));
	koreanWord_.SetMaxWidthAndHeight(D2D1::Point2F(maxWidth + 3.f, KOREAN_IDLE_FONT_SIZE));
	koreanWord_.SetFontName(L"YDIYGo530");
	koreanSize_ = D2D1::Point2F(object.GetWidth(), KOREAN_IDLE_FONT_SIZE);

	englishWord_.SetContents(object.GetEnglishName());
	englishWord_.SetFontSize(ENGLISH_IDLE_FONT_SIZE);
	englishWord_.SetPosition(D2D1::Point2F(0.f, KOREAN_IDLE_FONT_SIZE));
	englishWord_.SetMaxWidthAndHeight(D2D1::Point2F(maxWidth + 3.f, ENGLISH_IDLE_FONT_SIZE));
	englishWord_.SetFontName(L"Melor");
	englishSize_ = D2D1::Point2F(object.GetEnglishWidth(), ENGLISH_IDLE_FONT_SIZE);

	SetCenter(D2D1::Point2F(0.f, (KOREAN_IDLE_FONT_SIZE + ENGLISH_IDLE_FONT_SIZE) / 2.f));

	if (object.GetId() < Relationship::GetInstance()->GetFeels().size())
		isFeel_ = true;
	else
		isFeel_ = false;

	id_ = object.GetId();
	AddChild(&koreanWord_);
	AddChild(&englishWord_);
	if (IsFeel() == true)
	{
		koreanWord_.SetFontColor(FONTCOLOR_FEEL_UNFOCUS);
		englishWord_.SetFontColor(FONTCOLOR_FEEL_UNFOCUS);
	}
	else
	{
		koreanWord_.SetFontColor(FONTCOLOR_WORK_UNFOCUS);
		englishWord_.SetFontColor(FONTCOLOR_WORK_UNFOCUS);
	}
}


WordSprite::~WordSprite()
{
}

void WordSprite::Render()
{
	Component::Render();
}

void WordSprite::Update(float dTime)
{
	Component::Update(dTime);
	OnFocus();
	OnShuffle();
}

void WordSprite::OnShuffle()
{
	if (isShuffle_ == true)
	{
		float angle = 2 * M_PI * (rand() / (float)RAND_MAX);
		shuffleVelocity_ = shuffleVelocity_ + D2D1::Point2F(cos(angle) * SHUFFLE_ACCELERATION, sin(angle) * SHUFFLE_ACCELERATION);

		float pointSize = D2DPointSize(shuffleVelocity_);
		if (pointSize > SHUFFLE_MAX_VELOCITY)
		{
			shuffleVelocity_.x = shuffleVelocity_.x * SHUFFLE_MAX_VELOCITY / pointSize;
			shuffleVelocity_.y = shuffleVelocity_.y * SHUFFLE_MAX_VELOCITY / pointSize;
		}

		DoAnimate(POSITION, &(position_ + shuffleVelocity_), 1.f);
	}
}

void WordSprite::OnFocus()
{
	if (isFocus[GetId()] == true
		&& isFocus_ == false)
	{
		isFocus_ = true;

		if (IsFeel() == true)
		{
			koreanWord_.DoFontColorAnimate(FONTCOLOR_FEEL_FOCUS, 0.3f);
			englishWord_.DoFontColorAnimate(FONTCOLOR_FEEL_FOCUS, 0.3f);
		}
		else
		{
			koreanWord_.DoFontColorAnimate(FONTCOLOR_WORK_FOCUS, 0.3f);
			englishWord_.DoFontColorAnimate(FONTCOLOR_WORK_FOCUS, 0.3f);
		}
	}
	else if (isFocus[GetId()] == false
		&& isFocus_ == true)
	{
		isFocus_ = false;
		if (IsFeel() == true)
		{
			koreanWord_.DoFontColorAnimate(FONTCOLOR_FEEL_UNFOCUS, 0.3f);
			englishWord_.DoFontColorAnimate(FONTCOLOR_FEEL_UNFOCUS, 0.3f);
		}
		else
		{
			koreanWord_.DoFontColorAnimate(FONTCOLOR_WORK_UNFOCUS, 0.3f);
			englishWord_.DoFontColorAnimate(FONTCOLOR_WORK_UNFOCUS, 0.3f);
		}
	}
}
