#include "stdafx.h"
#include "Relationship.h"

Relationship* Relationship::pInstance_ = nullptr;

Relationship::Relationship()
{
}


Relationship::~Relationship()
{
	for each (auto& feel in feels_)
	{
		delete feel;
	}
	for each(auto& work in works_)
	{
		delete work;
	}

	feels_.clear();
	works_.clear();
}

bool Relationship::LoadDataFromFile(std::string filename)
{
	feels_.clear();
	works_.clear();

	std::wifstream ifs(filename);
	ifs.imbue(std::locale("kor"));
	if (ifs.eof())
		return false;

	int feelCount, workCount;
	std::wstring nameTemp;
	std::wstring englishNameTemp;
	float fontSizeTemp;
	float englishFontSizeTemp;
	ifs >> feelCount >> workCount;
	for (int i = 0; i < feelCount; i++)
	{
		ifs >> nameTemp >> fontSizeTemp >> englishNameTemp >> englishFontSizeTemp;
		feels_.push_back(new Feel(feels_.size(), nameTemp, fontSizeTemp, englishNameTemp, englishFontSizeTemp));
	}
	for (int i = 0; i < workCount; i++)
	{
		ifs >> nameTemp >> fontSizeTemp >> englishNameTemp >> englishFontSizeTemp;
		works_.push_back(new Work(works_.size(), nameTemp, fontSizeTemp, englishNameTemp, englishFontSizeTemp));
	}


	// init count_
	for each (auto& feel in feels_)
	{
		for each (auto& work in works_)
		{
			count_[std::make_pair(feel, work)] = 0;
		}
	}

	return true;
}
