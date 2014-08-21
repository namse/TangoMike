#include "stdafx.h"
#include "Feel.h"


Feel::Feel(int id, std::wstring name, float fontSize, std::wstring englishName, float englishFontSize)
	:Object()
{
	name_ = name;
	englishName_ = englishName;
	englishFontSize_ = englishFontSize;
	fontSize_ = fontSize;
	id_ = id;
}


Feel::~Feel()
{
}
