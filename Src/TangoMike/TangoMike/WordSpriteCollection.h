#pragma once
#include "stdafx.h"
#include "Component.h"
#include "WordSprite.h"
class WordSpriteCollection :
	public Component
{
public:
	WordSpriteCollection();
	~WordSpriteCollection();

	void Render();
	void Update(float dTime);

	void InitWordSprites();
	std::vector<WordSprite*> GetWordSprites() { return wordSprites_; }

private:
	std::vector<WordSprite*> wordSprites_;
};

