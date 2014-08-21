#pragma once
#include "stdafx.h"
class Object
{
public:
	Object();
	virtual ~Object();

	int GetId(){ return id_; }
	
	std::wstring GetName() { return name_; }
	std::wstring GetEnglishName() { return englishName_; }

	float getFontSize() { return fontSize_; }
	float getEnglishFontSize() { return englishFontSize_; }

protected:
	int id_;
	std::wstring name_;
	float fontSize_;

	std::wstring englishName_;
	float englishFontSize_;
};