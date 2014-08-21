#include "stdafx.h"
#include "Word.h"

Word::Word()
	: textAlignment_(DWRITE_TEXT_ALIGNMENT_LEADING),//DWRITE_TEXT_ALIGNMENT_LEADING
	paragraphAlignment_(DWRITE_PARAGRAPH_ALIGNMENT_NEAR),
	contents_(L""),
	fontName_(L"Calibri"),
	fontSize_(20.f)
{
	position_ = D2D1::Point2F();
}
Word::Word(std::wstring contents, D2D_POINT_2F position)
	: textAlignment_(DWRITE_TEXT_ALIGNMENT_LEADING),//DWRITE_TEXT_ALIGNMENT_LEADING
	paragraphAlignment_(DWRITE_PARAGRAPH_ALIGNMENT_NEAR),
	contents_(contents),
	fontName_(L"Calibri"),
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

	//hr = m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	hr = m_pTextFormat->SetTextAlignment(textAlignment_);



	m_pBackBufferRT->BeginDraw();

	m_pBackBufferRT->SetTransform(matrix_);



	m_pBackBufferRT->DrawText(
		contents_.c_str(),
		contents_.length(),
		m_pTextFormat,
		D2D1::RectF(0.f, 0.f, maxWidthAndHeight.x, maxWidthAndHeight.y),
		m_pTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_NONE
		);

	hr = m_pBackBufferRT->EndDraw();
	
	//m_pTextLayout->Release();
	//m_pTextFormat->Release();
	//SafeRelease(&m_pTextLayout);
	//SafeRelease(&m_pTextFormat);

}

void Word::Update(float dTime)
{
	Component::Update(dTime);
}
