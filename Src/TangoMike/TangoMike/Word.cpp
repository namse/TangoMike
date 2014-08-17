#include "stdafx.h"
#include "Word.h"

Word::Word(std::string contents, D2D_VECTOR_2F position)
	: textAlignment(DWRITE_TEXT_ALIGNMENT_LEADING),
	paragraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
{

}


Word::~Word()
{
}


void Word::Render()
{

}

void Word::Update(float dTime)
{

}