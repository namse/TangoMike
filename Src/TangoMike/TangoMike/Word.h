#pragma once
#include "stdafx.h"
#include "Component.h"
class Word : public Component
{
public:
	Word();
	Word(std::wstring contents, D2D_POINT_2F position);
	~Word();

	void virtual Render();
	void virtual Update(float dTime);
	
	void SetContents(std::wstring contents){
		contents_ = contents;
	}
	void SetFontSize(float size) {
		fontSize_ = size;
	}

	void SetTextAlignment(DWRITE_TEXT_ALIGNMENT align){
		textAlignment_ = align;
	}

	void SetMaxWidthAndHeight(D2D1_POINT_2F size){
		maxWidthAndHeight = size;
	}

	void SetFontColor(D2D_COLOR_F color){
		fontColor_ = color;
	}

	void DoFontSizeAnimate(float fontSize, float duration);
	void DoFontColorAnimate(D2D_COLOR_F color, float duration);

	void SetFontName(PCWSTR fontName)
	{
		fontName_ = fontName;
	}
	std::wstring GetContents(){ return contents_; }
private:
	
private:
	std::wstring contents_;
	PCWSTR fontName_;
	float fontSize_;
	DWRITE_TEXT_ALIGNMENT textAlignment_;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment_;
	D2D1_POINT_2F maxWidthAndHeight;
	D2D_COLOR_F fontColor_;

	Animation<float> fontSizeAnimation_;
	Animation<D2D_COLOR_F> fontColorAnimation_;
};

float DetermineMinWidth(float maxWidth, float maxHeight, IDWriteTextLayout * pTextLayout);