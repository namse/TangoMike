#include "stdafx.h"
#include "Line.h"

//85D5A3 E79F58
// Create a linear gradient.
static const D2D1_GRADIENT_STOP stops[] =
{
	{ 0.f, { ((float)0xde / (float)0xFF), ((float)0x96 / (float)0xFF), ((float)0x58 / (float)0xFF), 1.f } },
	{ 1.f, { ((float)0x84 / (float)0xFF), ((float)0xD3 / (float)0xFF), ((float)0xA2 / (float)0xFF), 1.f } },
};

Line::Line(D2D1_POINT_2F* point1, D2D1_POINT_2F* point2)
	:point1_(point1), point2_(point2), geometry_(nullptr), stops_(nullptr), brush_(nullptr)
{
	CalcBezier();

	if (rand()%2 == 0)
		lightBall_ = new LightBall(*point1_, point_bezier_, *point2_);
	else
		lightBall_ = new LightBall(*point2_, point_bezier_, *point1_);

	AddChild(lightBall_);
}

void Line::CalcBezier()
{
	float h = (((float)rand() / (float)RAND_MAX) * 0.4f) - 0.2f;
	float t = (((float)rand() / (float)RAND_MAX) * 1.6f) - 0.3f;

	D2D1_POINT_2F vec = *point2_ - *point1_;

	D2D1_POINT_2F vec_horizen = vec * t;
	D2D1_POINT_2F vec_vertical;
	vec_vertical.x = -vec.y;
	vec_vertical.y = vec.x;
	vec_vertical = vec_vertical * h;

	point_bezier_ = vec_vertical + vec_horizen + *point1_;
}

Line::~Line()
{
}

void Line::Render()
{
	Component::Render();

	HRESULT hr;

	if (geometry_ == nullptr)
	{
		hr = m_pD2DFactory->CreatePathGeometry(&geometry_);

		hr = geometry_->Open(&sink_);

		sink_->BeginFigure(
			D2D1::Point2F(point1_->x, point1_->y),
			D2D1_FIGURE_BEGIN_HOLLOW);

		float radius, angle;
		float length = sqrt(pow(point1_->x - point2_->x, 2) + pow(point1_->y - point2_->y, 2));
		float factor = 0.5f;//(float)(std::rand() % 10) / 100.f;
		radius = length * factor;
		angle = 1.5f;//(float)((float)std::rand() / (float)RAND_MAX) * M_PI * 2.0f;

		sink_->AddBezier(
			D2D1::BezierSegment(
			*point1_,
			point_bezier_, //D2D1::Point2F( point1_->x + radius * cos(angle), point1_->y + radius * sin(angle)),
			*point2_)
			);

		sink_->EndFigure(D2D1_FIGURE_END_OPEN);
		hr = sink_->Close();
	}

	if (stops_ == nullptr)
	{
		hr = m_pBackBufferRT->CreateGradientStopCollection(
			stops,
			ARRAYSIZE(stops),
			&stops_
			);
	}

	if (brush_ == nullptr)
	{
		hr = m_pBackBufferRT->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
			*point1_,
			*point2_),
			D2D1::BrushProperties(),
			stops_,
			&brush_
			);
	}
	// ÃÖÀûÈ­ : http://msdn.microsoft.com/ko-kr/library/windows/desktop/ee719658(v=vs.85).aspx
	m_pBackBufferRT->BeginDraw();

	m_pBackBufferRT->SetTransform(matrix_);

	m_pBackBufferRT->DrawGeometry(geometry_,
		brush_);
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
