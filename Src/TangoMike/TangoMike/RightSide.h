#pragma once
#include "stdafx.h"
#include "Component.h"
#include "WordSpriteCollection.h"
class RightSide :
	public Component
{
public:
	RightSide();
	~RightSide();


	void Render();
	void Update(float dTime);

	void SetArrange();
	void SetFocus();
	void SetIdle();

private:
	WordSpriteCollection wordSpriteCollection_;
};

