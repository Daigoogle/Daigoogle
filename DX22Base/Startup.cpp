#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include "Defines.h"
#include "Main.h"
#include "SingletonsMng.hxx"
#include <stdio.h>
#include <crtdbg.h>
#include "Window.h"

// timeGetTime周りの使用
#pragma comment(lib, "winmm.lib")

//--- プロトタイプ宣言
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Window& window = Window::GetInstance();
	window.SetHInstance(hInstance);
	window.SetNCmdShow(nCmdShow);


	// 初期化処理
	if (!Supervision::Initialize())
	{
		WNDCLASSEX wcex = window.GetWcex();
		Supervision::Finalize();
		UnregisterClass(wcex.lpszClassName, hInstance);
		return 0;
	}

	WNDCLASSEX wcex = window.GetWcex();
	MSG message = window.GetMessage();

	//--- FPS制御
	timeBeginPeriod(1);
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	//--- ウィンドウの管理
	while (1)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&message, NULL, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			DWORD nowTime = timeGetTime();
			float diff = static_cast<float>(nowTime - preExecTime);
			if (diff >= 1000.0f / 60)
			{
				Supervision::Updater();
				Supervision::Drawing();
				preExecTime = nowTime;
			}
		}
	}

	// 終了時
	timeEndPeriod(1);
	Supervision::Finalize();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;
}