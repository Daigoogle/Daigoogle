#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include "Defines.h"
#include "SingletonsMng.hxx"
#include <stdio.h>
#include <crtdbg.h>
#include "Window.h"
#include "DebugRestriction.hxx"
#include "Time.hxx"

// timeGetTime����̎g�p

//--- �v���g�^�C�v�錾
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	DEBUG_INIT

	Window& window = Window::GetInstance();
	window.SetHInstance(hInstance);
	window.SetNCmdShow(nCmdShow);

	TimerInit();

	// ����������
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

	//--- �E�B���h�E�̊Ǘ�
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

	// �I����
	timeEndPeriod(1);
	Supervision::Finalize();
	UnregisterClass(wcex.lpszClassName, hInstance);

	return 0;
}