#include "stdafx.h"
#include "Work.h"



Work::Work(int id, std::wstring name, float width, std::wstring englishName, float englishWidth)
	:Object()
{
	name_ = name;
	englishName_ = englishName;
	englishWidth_ = englishWidth;
	width_ = width;
	id_ = id;
}

Work::~Work()
{
}
