#include "stdafx.h"
#include "Word.h"


Word::Word(std::wstring contents, D2D_POINT_2F position)
	: textAlignment_(DWRITE_TEXT_ALIGNMENT_LEADING),//DWRITE_TEXT_ALIGNMENT_LEADING
	paragraphAlignment_(DWRITE_PARAGRAPH_ALIGNMENT_NEAR),
	contents_(contents),
	fontName_(L"¸¼Àº °íµñ"),
	fontSize_(20.f)
{
	position_ = position;
}


Word::~Word()
{
}


void Word::Render()
{
	Component::Render();

	HRESULT hr;


	hr = m_pDWriteFactory->CreateTextFormat(
		fontName_,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize_,
		L"", // locale
		&m_pTextFormat
		);
	hr = m_pTextFormat->SetTextAlignment(textAlignment_);
	hr = m_pTextFormat->SetParagraphAlignment(paragraphAlignment_);


	hr = m_pDWriteFactory->CreateTextLayout(
		contents_.c_str(),
		contents_.length(),
		m_pTextFormat,
		1000.f, 1000.f,
		&m_pTextLayout);

	m_pBackBufferRT->BeginDraw();

	m_pBackBufferRT->SetTransform(matrix_);



	m_pBackBufferRT->DrawText(
		contents_.c_str(),
		contents_.length(),
		m_pTextFormat,
		D2D1::RectF(0.f, 0.f , 100.f, fontSize_),
		m_pTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE
		);

	hr = m_pBackBufferRT->EndDraw();
	SafeRelease(&m_pTextLayout);
	SafeRelease(&m_pTextFormat);

}

void Word::Update(float dTime)
{
	Component::Update(dTime);
}
