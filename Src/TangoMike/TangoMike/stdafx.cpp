// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// TangoMike.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.



//Device-Dependent Resources
ID3D10Device *m_pDevice = NULL;
IDXGISwapChain *m_pSwapChain = NULL;
ID3D10RasterizerState *m_pState = NULL;
ID3D10RenderTargetView *m_pRenderTargetView = NULL;
ID3D10Texture2D *m_pLoupeTexture = NULL;
ID2D1Bitmap *m_pLoupeBitmap = NULL;

ID2D1RenderTarget *m_pBackBufferRT = NULL;

ID2D1SolidColorBrush *m_pTextBrush = NULL;
ID2D1SolidColorBrush *m_pLoupeBrush = NULL;
IDWriteTextLayout* m_pTextLayout = NULL;


ID2D1PathGeometry *m_pPathGeometry = NULL;
ID2D1GeometrySink *m_pGeometrySink = NULL;
ID2D1GradientStopCollection *m_pGradientStops = NULL;
ID2D1LinearGradientBrush *m_pLGBrush = NULL;

PendingAcceptList pendingAcceptList;

IWICImagingFactory* g_pWICFactory = nullptr;

ID2D1LinearGradientBrush *linebrush_[FEEL_COUNT][WORK_COUNT];
ID2D1GradientStopCollection* linestops_ = nullptr;

ID2D1LinearGradientBrush *linebrush_background[FEEL_COUNT][WORK_COUNT];
ID2D1GradientStopCollection* lineStopCollection_ = nullptr;
ID2D1GradientStopCollection* lineStopCollection_background = nullptr;
ID2D1BitmapRenderTarget *pCompatibleRenderTarget = nullptr;
bool isFocus[FEEL_COUNT + WORK_COUNT] = { false, };
float distance(D2D1_POINT_2F* a, D2D1_POINT_2F* b)
{
	return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}
bool didDrawBackground = false;
float g_opacity = 0.3f;
float g_lineThickness = 0.3f;