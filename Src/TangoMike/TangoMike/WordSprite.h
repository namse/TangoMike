#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Word.h"
#include "Object.h"
class WordSprite :
	public Component
{
public:
	WordSprite(Object& object);
	~WordSprite();

	void Render();
	void Update(float dTime);

	void SetTextAlignment(DWRITE_TEXT_ALIGNMENT align) {
		koreanWord_.SetTextAlignment(align);
		englishWord_.SetTextAlignment(align);
	}

	void SetMaxWidthAndHeight(D2D1_POINT_2F koreanSize, D2D1_POINT_2F englishSize){
		koreanSize_ = koreanSize;
		englishSize_ = englishSize;
	}

	float GetMaxWidth(){
		return max(koreanSize_.x, englishSize_.x);
	}

private:
	Word koreanWord_;
	Word englishWord_;

	D2D1_POINT_2F koreanSize_;
	D2D1_POINT_2F englishSize_;

};

