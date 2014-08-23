#include "stdafx.h"
#include "Line.h"

//85D5A3 E79F58
// Create a linear gradient.
static const D2D1_GRADIENT_STOP stops[] =
{
	{ 0.f, { ((float)0x85 / (float)0xFF), ((float)0xD5 / (float)0xFF), ((float)0xA3 / (float)0xFF), 1.f } },
	{ 1.f, { ((float)0xE7 / (float)0xFF), ((float)0x9F / (float)0xFF), ((float)0x58 / (float)0xFF), 1.f } },
};

Line::Line(D2D1_POINT_2F* point1, D2D1_POINT_2F* point2)
	:point1_(point1), point2_(point2)
{

}


Line::~Line()
{
}

void Line::Render()
{
	Component::Render();
	HRESULT hr;
	hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometry);

	hr = m_pPathGeometry->Open(&m_pGeometrySink);

	m_pGeometrySink->BeginFigure(
		D2D1::Point2F(point1_->x, point1_->y),
		D2D1_FIGURE_BEGIN_HOLLOW);

	float radius, angle;
	float length = sqrt(pow(point1_->x - point2_->x, 2) + pow(point1_->y - point2_->y, 2));
	float factor = 0.5f;//(float)(std::rand() % 10) / 100.f;
	radius = length * factor;
	angle = 1.5f;//(float)((float)std::rand() / (float)RAND_MAX) * M_PI * 2.0f;

	m_pGeometrySink->AddBezier(
		D2D1::BezierSegment(
		*point1_,
		*point1_, //D2D1::Point2F( point1_->x + radius * cos(angle), point1_->y + radius * sin(angle)),
		*point2_)
		);

	m_pGeometrySink->EndFigure(D2D1_FIGURE_END_OPEN);

	hr = m_pGeometrySink->Close();

	if (m_pGradientStops == nullptr)
	{
		hr = m_pBackBufferRT->CreateGradientStopCollection(
			stops,
			ARRAYSIZE(stops),
			&m_pGradientStops
			);
	}

	if (m_pLGBrush == nullptr)
	{
		hr = m_pBackBufferRT->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
			*point1_,
			*point2_),
			D2D1::BrushProperties(),
			m_pGradientStops,
			&m_pLGBrush
			);
	}
	// ÃÖÀûÈ­ : http://msdn.microsoft.com/ko-kr/library/windows/desktop/ee719658(v=vs.85).aspx
	m_pBackBufferRT->BeginDraw();

	m_pBackBufferRT->SetTransform(matrix_);

	m_pBackBufferRT->DrawGeometry(m_pPathGeometry,
		m_pLGBrush);
	hr = m_pBackBufferRT->EndDraw();

	//m_pGradientStops->Release();
	//m_pLGBrush->Release();
	//SafeRelease(&m_pGradientStops);
	//SafeRelease(&m_pLGBrush);
	//SafeRelease(&m_pPathGeometry);
	//SafeRelease(&m_pGeometrySink);
}

void Line::Update(float dTime)
{
	Component::Update(dTime);
}
