#pragma once
#include "stdafx.h"
#include "Object.h"
class Feel : public Object
{
public:
	Feel(int id, std::wstring name, float width, std::wstring englishName, float englishWidth);
	~Feel();
};

