#pragma once
#include "stdafx.h"
class Object
{
public:
	Object(int id, std::wstring name, float width, std::wstring englishName, float englishWidth);
	virtual ~Object();

	int GetId(){ return id_; }
	
	std::wstring GetName() { return name_; }
	std::wstring GetEnglishName() {
		return englishName_;
	}

	std::wstring GetNameOnXML();
	float GetWidth() { return width_; }
	float GetEnglishWidth() { return englishWidth_; }

protected:
	int id_;
	std::wstring name_;
	std::wstring name_WithoutSpace;
	float width_;

	std::wstring englishName_;
	std::wstring englishName_WithoutSpace;
	float englishWidth_;

	std::wstring name_forXML;
};