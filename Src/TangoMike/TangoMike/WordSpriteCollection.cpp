#include "stdafx.h"
#include "WordSpriteCollection.h"
#include "Relationship.h"

WordSpriteCollection::WordSpriteCollection()
{
}


WordSpriteCollection::~WordSpriteCollection()
{

	for (auto& wordSprite : wordSprites_)
	{
		delete wordSprite;
	}
}


void WordSpriteCollection::Render()
{
	Component::Render();
}


void WordSpriteCollection::Update(float dTime)
{
	Component::Update(dTime);
}

void WordSpriteCollection::InitWordSprites()
{
	for (auto& feel : Relationship::GetInstance()->GetFeels())
	{
		WordSprite* sprite = new WordSprite((Object)(*feel));
		wordSprites_.push_back(sprite);
	}

	for (auto& work : Relationship::GetInstance()->GetWorks())
	{
		WordSprite* sprite = new WordSprite((Object)(*work));
		wordSprites_.push_back(sprite);
	}

	for (auto& wordSprite : wordSprites_)
	{
		AddChild(wordSprite);
	}
}
