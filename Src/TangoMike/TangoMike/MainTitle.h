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
	Word word1, word2, word3;
};

