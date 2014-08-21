// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "stdafx.h"
#include "TangoMike.h"
#include "Relationship.h"
#include "Word.h"
#include "Line.h"
#include "MainTitle.h"
#include "RightSide.h"
/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/

void DevConsoleCreate();
int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{
	DevConsoleCreate();
	std::srand(unsigned(std::time(0)));
	Relationship::GetInstance()->LoadDataFromFile("data.txt");

	// Ignoring the return value because we want to continue running even in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			Application app;

			if (SUCCEEDED(app.Initialize()))
			{
				MainTitle mainTitle;
				RightSide rightSide;
				app.AddChild(&mainTitle);
				app.AddChild(&rightSide);
				
				/*auto feels = Relationship::GetInstance()->GetFeels();
				auto works = Relationship::GetInstance()->GetWorks();
				std::vector<D2D_POINT_2F*>feelsPositions;
				std::vector<D2D_POINT_2F*>worksPositions;

				int totalCount = feels.size() + works.size();
				D2D_POINT_2F center;
				center.x = 512.f, center.y = 384.f;
				float radius = 300.f;
				for (int i = 0; i < feels.size(); i++)
				{
					float angle = 2.f * M_PI * (float)i / (float)(totalCount);

					D2D_POINT_2F pos;
					pos.x = center.x + cosf(angle) * radius;
					pos.y = center.y + sinf(angle) * radius;
					Word* word = new Word(feels[i]->GetName(), pos);
					if (angle < M_PI_2 || angle > M_PI + M_PI_2)
					{
						word->SetRotation(angle);
					}
					else
					{
						word->SetRotation(M_PI + angle);
					}
					app.AddChild(word);

					feelsPositions.push_back(word->GetPosition());
				}
				for (int i = 0; i < works.size(); i++)
				{
					float angle = 2.f * M_PI * (float)(i + feels.size()) / (float)(totalCount);
					D2D_POINT_2F pos;
					pos.x = center.x + cosf(angle) * radius;
					pos.y = center.y + sinf(angle) * radius;
					Word* word = new Word(works[i]->GetName(), pos);
					if (angle < M_PI_2 || angle > M_PI + M_PI_2)
					{
						word->SetRotation(angle);
					}
					else
					{
						word->SetRotation(M_PI + angle);
					}
					app.AddChild(word);

					worksPositions.push_back(word->GetPosition());
				}

				for (auto feelPositoin : feelsPositions)
				{
					for (auto workPosition : worksPositions)
					{
						//for (int i = 0; i < rand() % 5; i++)
							app.AddChild(new Line(feelPositoin, workPosition));
					}
				}
*/

				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}
void DevConsoleCreate(){

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	int consoleHandleR, consoleHandleW;
	long stdioHandle;
	FILE *fptr;

	AllocConsole();
	std::wstring strW = L"Dev Console";
	SetConsoleTitle(strW.c_str());

	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
	DrawMenuBar(GetConsoleWindow());

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	/*
	stdioHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	consoleHandleR = _open_osfhandle(stdioHandle, _O_TEXT);
	fptr = _fdopen(consoleHandleR, "r");
	*stdin = *fptr;
	setvbuf(stdin, NULL, _IONBF, 0);

	stdioHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandleW = _open_osfhandle(stdioHandle, _O_TEXT);
	fptr = _fdopen(consoleHandleW, "w");
	*stdout = *fptr;
	setvbuf(stdout, NULL, _IONBF, 0);

	stdioHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	*stderr = *fptr;
	setvbuf(stderr, NULL, _IONBF, 0);*/

}