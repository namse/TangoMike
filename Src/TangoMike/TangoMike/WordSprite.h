#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Word.h"
#include "Object.h"
class WordSprite :
	public Component
{
public:
	WordSprite(Object& object);
	~WordSprite();


private:
	Word koreanWord_;
	Word englishWord_;
};

