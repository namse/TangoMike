#include "stdafx.h"
#include "Work.h"



Work::Work(int id, std::wstring name, float fontSize, std::wstring englishName, float englishFontSize)
	:Object()
{
	englishName_ = englishName;
	englishFontSize_ = englishFontSize;
	fontSize_ = fontSize;
	name_ = name;
	id_ = id;
}


Work::~Work()
{
}
