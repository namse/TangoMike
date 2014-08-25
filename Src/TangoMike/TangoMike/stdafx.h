// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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
#include <queue>

////
#include "d2dPointOperator.h"
#include "d2dColorOperator.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "animation.h"

#include "ProducerConsumerQueue.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


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

#define KOREAN_IDLE_FONT_SIZE 15.f
#define KOREAN_FOCUS_FONT_SIZE 22.f

#define ENGLISH_IDLE_FONT_SIZE 11.f
#define ENGLISH_FOCUS_FONT_SIZE 22.f

#define SHUFFLE_ACCELERATION 1.f
#define SHUFFLE_MAX_VELOCITY 5.f

#define CIRCLE_RADIUS_TO_POINT 269.f
#define POINT_TO_WORD 14.f
#define CIRCLE_RADIUS_TO_WORD (CIRCLE_RADIUS_TO_POINT + POINT_TO_WORD)

#define CIRCLE_CENTER_POSITION D2D1::Point2F(573.f, 375.f)

#define POINT_RADIUS_FOCUS 5.5f
#define POINT_RADIUS_UNFOCUS 2.f

#define FONTCOLOR_FEEL_FOCUS D2D1::ColorF( 0xde9658)
#define FONTCOLOR_WORK_FOCUS D2D1::ColorF( 0x84d3a2)
#define FONTCOLOR_FEEL_UNFOCUS D2D1::ColorF( 0xde9658, 0.35f)
#define FONTCOLOR_WORK_UNFOCUS D2D1::ColorF( 0x84d3a2, 0.35f)

#define COLOR_FEEL FONTCOLOR_FEEL_FOCUS
#define COLOR_WORK FONTCOLOR_WORK_FOCUS

#define TITLE_RECT D2D1::RectF(0.f,0.f,120.f,100.f)
#define TITLE_POSTION D2D1::Point2F(39.f, 53.f)

#define TOTAL_COUNT_CONTENTS_TOTAL_USERS L"Total Users"
#define TOTAL_COUNT_CONTENTS_TOP_PICKS L"Top Picks : word / work"
#define TOTAL_COUNT_CONTENTS_TOP_COMMUNION L"Top Communion"

#define TOTAL_COUNT_POSITION_TOTAL_USERS D2D1::Point2F(49.f, 192.f)
#define TOTAL_COUNT_POSITION_TOTAL_USERS_NUMBER D2D1::Point2F(48.f, 207.f)
#define TOTAL_COUNT_POSITION_TOP_PICK D2D1::Point2F(49.f, 262.f)
#define TOTAL_COUNT_POSITION_TP_KOREAN_FEEL D2D1::Point2F(48.f, 280.f)
#define TOTAL_COUNT_POSITION_TP_ENGLISH_FEEL D2D1::Point2F(49.f, 296.f)
#define TOTAL_COUNT_POSITION_TP_COUNT_FEEL D2D1::Point2F(48.f, 309.f)
#define TOTAL_COUNT_POSITION_TP_KOREAN_WORK D2D1::Point2F(48.f, 342.f)
#define TOTAL_COUNT_POSITION_TP_ENGLISH_WORK D2D1::Point2F(49.f, 361.f)
#define TOTAL_COUNT_POSITION_TP_COUNT_WORK D2D1::Point2F(48.f, 374.f)
#define TOTAL_COUNT_POSITION_TOP_COMMUNION D2D1::Point2F(49.f, 423.f)
#define TOTAL_COUNT_POSITION_TC_KOREAN_FEEL D2D1::Point2F(49.f, 438.f)
#define TOTAL_COUNT_POSITION_TC_ENGLISH_FEEL D2D1::Point2F(49.f, 454.f)
#define TOTAL_COUNT_POSITION_TC_KOREAN_WORK D2D1::Point2F(49.f, 471.f)
#define TOTAL_COUNT_POSITION_TC_ENGLISH_WORK D2D1::Point2F(49.f, 485.f)
#define TOTAL_COUNT_POSITION_TC_COUNT D2D1::Point2F(48.f, 502.f)

#define TOTAL_COUNT_FONTSIZE_TITLE 10.f
#define TOTAL_COUNT_FONTSIZE_TU_COUNT 32.f
#define TOTAL_COUNT_FONTSIZE_TP_KOREAN 15.f
#define TOTAL_COUNT_FONTSIZE_TP_ENGLSIH 11.f
#define TOTAL_COUNT_FONTSIZE_TP_COUNT 24.f
#define TOTAL_COUNT_FONTSIZE_TC_KOREAN 13.f
#define TOTAL_COUNT_FONTSIZE_TC_ENGLISH 10.f
#define TOTAL_COUNT_FONTSIZE_TC_COUNT 24.f

#define TOTAL_COUNT_FONTNAME_TITLE L"Helvetica Neue"
#define TOTAL_COUNT_FONTNAME_KOREAN L"Yoon 윤고딕 520_TT"
#define TOTAL_COUNT_FONTNAME_ENGLSIH L"Melor-Thin"
#define TOTAL_COUNT_FONTNAME_COUNT L"Rix고딕 L"

#define TOTAL_COUNT_FONTCOLOR_TITLE D2D1::ColorF( 0xFFFFFF)
#define TOTAL_COUNT_FONTCOLOR_COUNT D2D1::ColorF( 0xFFFFFF)

#define LIGHT_BALL_MAX_RADIUS 4.f

#define MAX_LINE_COUNT 3

#define FEEL_COUNT 18
#define WORK_COUNT 18

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
#define MAIN_TITLE_FILE_NAME L"title.png"
#define XML_BACKUP_NAME L"backup.xml"

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

extern IWICImagingFactory* g_pWICFactory;

extern ID2D1LinearGradientBrush *linebrush_[FEEL_COUNT][WORK_COUNT];
extern ID2D1LinearGradientBrush *linebrush_background[FEEL_COUNT][WORK_COUNT];
extern ID2D1GradientStopCollection* lineStopCollection_;
extern ID2D1GradientStopCollection* lineStopCollection_background;
extern ID2D1BitmapRenderTarget *pCompatibleRenderTarget;
static const D2D1_GRADIENT_STOP lineStops[] =
{
	{ 0.f, { ((float)0xde / (float)0xFF), ((float)0x96 / (float)0xFF), ((float)0x58 / (float)0xFF), 1.f } },
	{ 1.f, { ((float)0x84 / (float)0xFF), ((float)0xD3 / (float)0xFF), ((float)0xA2 / (float)0xFF), 1.f } },
};
static const D2D1_GRADIENT_STOP lineStops_background[] =
{
	{ 0.f, { ((float)0xde / (float)0xFF), ((float)0x96 / (float)0xFF), ((float)0x58 / (float)0xFF), 0.15f } },
	{ 1.f, { ((float)0x84 / (float)0xFF), ((float)0xD3 / (float)0xFF), ((float)0xA2 / (float)0xFF), 0.15f } },
};
static const D2D1_GRADIENT_STOP lightBallStops[] =
{
	{ 0.f, { 1.f, 1.f, 1.f, 1.f } },
	{ 1.f, { 1.f, 1.f, 1.f, 0.f } },
};

inline ID2D1LinearGradientBrush* GetLineBrush(int feelID, int workID){
	return linebrush_[feelID][workID - FEEL_COUNT];
};

inline ID2D1LinearGradientBrush* GetLineBrush_Background(int feelID, int workID){
	return linebrush_background[feelID][workID - FEEL_COUNT];
};
//for server
/// accepting list
typedef ProducerConsumerQueue<SOCKET, 100> PendingAcceptList;
extern PendingAcceptList pendingAcceptList;

extern bool isFocus[FEEL_COUNT + WORK_COUNT];

float distance(D2D1_POINT_2F* a, D2D1_POINT_2F* b);
