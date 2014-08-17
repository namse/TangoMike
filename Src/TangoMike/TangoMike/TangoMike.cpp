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
/******************************************************************
*                                                                 *
*  WinMain                                                        *
*                                                                 *
*  Application entrypoint                                         *
*                                                                 *
******************************************************************/

int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{

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

				auto feels = Relationship::GetInstance()->GetFeels();
				auto works = Relationship::GetInstance()->GetWorks();

				int totalCount = feels.size() + works.size();
				D2D_VECTOR_2F center;
				center.x = 500.f, center.y = 500.f;
				float radius = 100.f;
				for (int i = 0; i < feels.size(); i++)
				{
					float angle = 2.f * M_PI * (float)i / (float)(totalCount);

					D2D_VECTOR_2F pos;
					pos.x = center.x + cosf(angle) * radius;
					pos.y = center.y + sinf(angle) * radius;
					app.AddChild(new Word(feels[i]->GetName(), pos));
				}
				for (int i = 0; i < works.size(); i++)
				{
					float angle = 2.f * M_PI * (float)(i + feels.size()) / (float)(totalCount);
					D2D_VECTOR_2F pos;
					pos.x = center.x + cosf(angle) * radius;
					pos.y = center.y + sinf(angle) * radius;
					app.AddChild(new Word(works[i]->GetName(), pos));
				}

				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}
