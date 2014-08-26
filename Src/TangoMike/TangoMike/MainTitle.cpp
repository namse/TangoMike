#include "stdafx.h"
#include "MainTitle.h"


MainTitle::MainTitle() : mD2DBitmap(nullptr)
{
	SetPosition(TITLE_POSTION);
}


MainTitle::~MainTitle()
{
}


void MainTitle::Update(float dTime)
{
	Component::Update(dTime);
}

void MainTitle::Render()
{
	Component::Render();


	if (mD2DBitmap == nullptr)
	{
		if (g_pWICFactory == nullptr)
		{
			HRESULT ret = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pWICFactory));
			if (ret == REGDB_E_CLASSNOTREG)
			{
				CoCreateInstance(CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pWICFactory));
			}
		}

		IWICBitmapDecoder* bitmapDecoder = nullptr;
		g_pWICFactory->CreateDecoderFromFilename(MAIN_TITLE_FILE_NAME, nullptr, GENERIC_READ,
			WICDecodeMetadataCacheOnDemand, &bitmapDecoder);

		IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
		bitmapDecoder->GetFrame(0, &bitmapFrameDecode);

		g_pWICFactory->CreateFormatConverter(&mFmtConverter);

		mFmtConverter->Initialize(bitmapFrameDecode,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom);

		m_pBackBufferRT->CreateBitmapFromWicBitmap(mFmtConverter, nullptr, &mD2DBitmap);

		bitmapDecoder->Release();
		bitmapFrameDecode->Release();
	}
	m_pBackBufferRT->BeginDraw();
	m_pBackBufferRT->SetTransform(matrix_);
	m_pBackBufferRT->DrawBitmap(mD2DBitmap, TITLE_RECT);
	HRESULT hr = m_pBackBufferRT->EndDraw();
	
}