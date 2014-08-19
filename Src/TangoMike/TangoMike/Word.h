#pragma once
#include "stdafx.h"
#include "Component.h"
class Word : public Component
{
public:
	Word(std::wstring contents, D2D_POINT_2F position);
	~Word();

	void virtual Render();
	void virtual Update(float dTime);

private:
	
private:
	std::wstring contents_;
	PCWSTR fontName_;
	float fontSize_;
	DWRITE_TEXT_ALIGNMENT textAlignment_;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment_;
};

float DetermineMinWidth(float maxWidth, float maxHeight, IDWriteTextLayout * pTextLayout);