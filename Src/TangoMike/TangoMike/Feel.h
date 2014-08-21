#pragma once
#include "stdafx.h"
#include "Object.h"
class Feel : public Object
{
public:
	Feel(int id, std::wstring name, float fontSize, std::wstring englishName, float englishFontSize);
	~Feel();
};

