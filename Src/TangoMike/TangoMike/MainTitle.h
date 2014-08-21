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
	Word word1_, word2_, word3_;
};

