#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include "Defines.h"
#include "SingletonsMng.hxx"
#include <stdio.h>
#include <crtdbg.h>
#include "Window.h"
#include "DebugRestriction.hxx"
#include "Time.hxx"

// timeGetTime周りの使用

//--- プロトタイプ宣言
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DEBUG_INIT

	Window& window = Window::GetInstance();
	window.SetHInstance(hInstance);
	window.SetNCmdShow(nCmdShow);

	TimerInit();

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

	TimerUpdate();

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
			
			DebugString_(std::to_string(GetFPS()))
			{
				Supervision::Updater();
				TimerUpdate();
			}
		}
	}

	// 終了時
	timeEndPeriod(1);
	Supervision::Finalize();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;
}