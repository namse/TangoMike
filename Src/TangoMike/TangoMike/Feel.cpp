#include "stdafx.h"
#include "Feel.h"


Feel::Feel(int id, std::wstring name, float width, std::wstring englishName, float englishWidth)
	:Object()
{
	name_ = name;
	englishName_ = englishName;
	englishWidth_ = englishWidth;
	width_ = width;
	id_ = id;
}


Feel::~Feel()
{
}
