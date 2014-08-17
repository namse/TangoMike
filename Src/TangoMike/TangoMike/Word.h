#pragma once
#include "stdafx.h"
#include "Component.h"
class Word : public Component
{
public:
	Word(std::string contents, D2D_VECTOR_2F position);
	~Word();

	void virtual Render();
	void virtual Update(float dTime);

private:
	std::string contents_;

	DWRITE_TEXT_ALIGNMENT textAlignment;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment;
};

