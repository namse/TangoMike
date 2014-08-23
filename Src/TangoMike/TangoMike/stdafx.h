// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#pragma warning(disable : 4018)

#include "targetver.h"


// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows XP or later.
#define WINVER 0x0501       // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501 // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE           // Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600    // Change this to the appropriate value to target other versions of IE.
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers

#define _CRT_SECURE_NO_WARNINGS
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>

#include <d3d10_1.h>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <strsafe.h>
#include <string>
#include<map>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <atlconv.h>
#include <ctime>
#include <set>

#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <assert.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <atomic>
#include <typeinfo>

////
#include "d2dPointOperator.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "animation.h"

#include "ProducerConsumerQueue.h"


//////////////////////////////////////////////////////////////////////////

/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/

template<class Interface>
inline void
SafeRelease(
Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define TIME_RING_BUFFER_SIZE 10

#define KOREAN_IDLE_FONT_SIZE 13.f
#define KOREAN_FOCUS_FONT_SIZE 22.f

#define ENGLISH_IDLE_FONT_SIZE 13.f
#define ENGLISH_FOCUS_FONT_SIZE 22.f

#define SHUFFLE_ACCELERATION 1.f
#define SHUFFLE_MAX_VELOCITY 5.f

#define FONTCOLOR_FEEL_FOCUS D2D1::ColorF( 0x84d3a2)
#define FONTCOLOR_WORK_FOCUS D2D1::ColorF( 0x84d3a2)
#define FONTCOLOR_FEEL_UNFOCUS D2D1::ColorF( 0x84d3a2, 0.35f)
#define FONTCOLOR_WORK_UNFOCUS D2D1::ColorF( 0x84d3a2, 0.35f)
#include "ringbuffer.h"

namespace MyAntialiasMode
{
	enum Enum
	{
		Aliased = 0,
		PerPrimitive,
		MSAA,
		Count
	};
}


namespace SampleType
{
	enum Enum
	{
		Filled,
		Wireframe,
		Count
	};
}

#define XML_FILE_NAME L"positionInfo.xml"


//Device-Dependent Resources
extern ID3D10Device *m_pDevice;
extern IDXGISwapChain *m_pSwapChain;
extern ID3D10RasterizerState *m_pState;
extern ID3D10RenderTargetView *m_pRenderTargetView;
extern ID3D10Texture2D *m_pLoupeTexture;
extern ID2D1Bitmap *m_pLoupeBitmap;

extern ID2D1RenderTarget *m_pBackBufferRT;

extern ID2D1SolidColorBrush *m_pTextBrush;
extern ID2D1SolidColorBrush *m_pLoupeBrush;

// Device-Independent Resources
extern ID2D1Factory *m_pD2DFactory;
extern IDWriteFactory *m_pDWriteFactory;
extern IDWriteTextFormat *m_pTextFormat;
extern IDWriteTextLayout* m_pTextLayout;

extern ID2D1PathGeometry *m_pPathGeometry;

extern ID2D1GeometrySink *m_pGeometrySink;
extern ID2D1GradientStopCollection *m_pGradientStops;
extern ID2D1LinearGradientBrush *m_pLGBrush;

//for server
/// accepting list
typedef ProducerConsumerQueue<SOCKET, 100> PendingAcceptList;
extern PendingAcceptList pendingAcceptList;
#define FEEL_COUNT 18
#define WORK_COUNT 18