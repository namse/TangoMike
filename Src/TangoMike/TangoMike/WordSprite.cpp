#include "stdafx.h"
#include "WordSprite.h"



WordSprite::WordSprite(Object& object)
	:koreanWord_()
{
	AddChild(&koreanWord_);
	AddChild(&englishWord_);
}


WordSprite::~WordSprite()
{
}
