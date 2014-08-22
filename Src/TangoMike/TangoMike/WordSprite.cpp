#include "stdafx.h"
#include "WordSprite.h"



WordSprite::WordSprite(Object& object)
{
	float maxWidth = max(object.GetWidth(), object.GetEnglishWidth());

	koreanWord_.SetContents(object.GetName());
	koreanWord_.SetFontSize(KOREAN_IDLE_FONT_SIZE);
	koreanWord_.SetPosition(D2D1::Point2F(0.f, 0.f));
	koreanWord_.SetMaxWidthAndHeight(D2D1::Point2F(maxWidth, KOREAN_IDLE_FONT_SIZE));
	koreanSize_ = D2D1::Point2F(object.GetWidth(), KOREAN_IDLE_FONT_SIZE);

	englishWord_.SetContents(object.GetEnglishName());
	englishWord_.SetFontSize(ENGLISH_IDLE_FONT_SIZE);
	englishWord_.SetPosition(D2D1::Point2F(0.f, KOREAN_IDLE_FONT_SIZE));
	englishWord_.SetMaxWidthAndHeight(D2D1::Point2F(maxWidth, ENGLISH_IDLE_FONT_SIZE));
	englishSize_ = D2D1::Point2F(object.GetEnglishWidth(), ENGLISH_IDLE_FONT_SIZE);


	AddChild(&koreanWord_);
	AddChild(&englishWord_);
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
