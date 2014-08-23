#include "stdafx.h"
#include "MainTitle.h"


MainTitle::MainTitle()
	:word1_(), word2_(), word3_(), mD2DBitmap(nullptr)
{
	SetPosition(TITLE_POSTION);
	//LoadTextFromXml();
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

void MainTitle::LoadTextFromXml()
{
	pugi::xml_document doc;
	auto result = doc.load_file(XML_FILE_NAME);
	

	if (result)
	{
		std::cout << "Success description: " << result.description() << "\n";

		auto xmlMainTitle = doc.child(L"ShowItems").child(L"MainTitle");

		auto xmlWord1 = xmlMainTitle.child(L"Word1");
		word1_.SetContents(xmlWord1.attribute(L"Contents").value());
		word1_.SetPosition(
			D2D1::Point2F(xmlWord1.attribute(L"Left").as_int(), xmlWord1.attribute(L"Top").as_int()));
		word1_.SetFontSize(xmlWord1.attribute(L"FontSize").as_float());
		word1_.SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));

		auto xmlWord2 = xmlMainTitle.child(L"Word2");
		word2_.SetContents(xmlWord2.attribute(L"Contents").value());
		word2_.SetPosition(
			D2D1::Point2F(xmlWord2.attribute(L"Left").as_int(), xmlWord2.attribute(L"Top").as_int()));
		word2_.SetFontSize(xmlWord2.attribute(L"FontSize").as_float());
		word2_.SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));

		auto xmlWord3 = xmlMainTitle.child(L"Word3");
		word3_.SetContents(xmlWord3.attribute(L"Contents").value());
		word3_.SetPosition(
			D2D1::Point2F(xmlWord3.attribute(L"Left").as_int(), xmlWord3.attribute(L"Top").as_int()));
		word3_.SetFontSize(xmlWord3.attribute(L"FontSize").as_float());
		word3_.SetMaxWidthAndHeight(D2D1::Point2F(1000.f, 1000.f));

	}
	else
	{
		std::cout << "Error description: " << result.description() << "\n";
		std::cout << "Error offset: " << result.offset << " (error at [..." << (XML_FILE_NAME + result.offset) << "]\n\n";
		Assert("error load xml");
	}

}
