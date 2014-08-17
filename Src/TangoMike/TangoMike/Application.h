#pragma once
/******************************************************************
*                                                                 *
*  Application                                                  *
*                                                                 *
******************************************************************/

class Application
{
public:
	Application();
	~Application();

	HRESULT Initialize();

	void RunMessageLoop();

private:
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

	HRESULT OnRender();

	void OnMouseMove(
		LPARAM lParam
		);

	void OnKeyDown(
		SHORT vkey
		);

	void OnWheel(
		WPARAM w
		);

	float GetZoom()
	{
		return powf(2.0f, m_logZoom / WHEEL_DELTA);
	}

	PCWSTR GetAntialiasModeString();

	HRESULT RenderD2DContentIntoSurface(
		float time
		);

	HRESULT RenderLoupe();

	HRESULT RenderTextInfo();

	HRESULT CreateD3DDevice(
		IDXGIAdapter *pAdapter,
		D3D10_DRIVER_TYPE driverType,
		UINT flags,
		ID3D10Device1 **ppDevice
		);

	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
		);

private:
	HWND m_hwnd;

	MyAntialiasMode::Enum m_antialiasMode;
	SampleType::Enum m_sampleType;
	bool m_paused;
	bool m_drawLoupe;
	UINT m_numSquares;
	float m_logZoom;
	D2D1_POINT_2F m_mousePos;
	LONGLONG m_pausedTime;
	LONGLONG m_timeDelta;
	RingBuffer<LONGLONG, TIME_RING_BUFFER_SIZE> m_times;

	//Device-Dependent Resources
	ID3D10Device *m_pDevice;
	IDXGISwapChain *m_pSwapChain;
	ID3D10RasterizerState *m_pState;
	ID3D10RenderTargetView *m_pRenderTargetView;
	ID3D10Texture2D *m_pLoupeTexture;
	ID2D1Bitmap *m_pLoupeBitmap;

	ID2D1RenderTarget *m_pBackBufferRT;

	ID2D1SolidColorBrush *m_pTextBrush;
	ID2D1SolidColorBrush *m_pLoupeBrush;

	// Device-Independent Resources
	ID2D1Factory *m_pD2DFactory;
	IDWriteFactory *m_pDWriteFactory;
	IDWriteTextFormat *m_pTextFormat;
};

