#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Word.h"
class MainTitle :
	public Component
{
public:
	MainTitle();
	~MainTitle();

	void Update(float dTime);
	void Render();

private:
	void LoadTextFromXml();

private:
	IWICFormatConverter* mFmtConverter;
	ID2D1Bitmap* mD2DBitmap;
};

