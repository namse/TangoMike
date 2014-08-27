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

	void SetShuffle(bool isShuffle){
		isShuffle_ = isShuffle;
		shuffleVelocity_ = D2D1::Point2F();
	}

	Word* GetKoreanWord(){ return &koreanWord_; }
	Word* GetEnglishWord(){ return &englishWord_; }

	int GetId(){ return id_; }

	bool IsFocus(){ return isFocus_; }

	bool IsFeel()
	{
		return isFeel_;
	}

	bool IsWork()
	{
		return !IsFeel();
	}
private:
	void OnShuffle();
	void OnFocus();
private:
	Word koreanWord_;
	Word englishWord_;

	D2D1_POINT_2F koreanSize_;
	D2D1_POINT_2F englishSize_;

	bool isShuffle_;
	D2D_POINT_2F shuffleVelocity_;

	bool isFocus_;

	bool isFeel_;

	int id_;
};

