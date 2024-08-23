#ifndef _____WINDOW_H_____
#define _____WINDOW_H_____

#include <windows.h>
#include "SingletonsMng.hxx"

class Window :public Singleton<Window>
{
	friend class Singleton<Window>;
public:
	bool Init();
	void Update();

	void SetHInstance(HINSTANCE hInst) { hInstance = hInst; }
	void SetNCmdShow(int nCmd) { nCmdShow = nCmd; }

	HWND GetHWnd() { return hWnd; }
	WNDCLASSEX GetWcex() { return wcex; }
	UINT GetScreenWidth() { return SCREEN_WIDTH; }
	UINT GetScreenHeight() { return SCREEN_HEIGHT; }
	MSG GetMessage() { return message; }

	bool IsFullScreen() { return false; }
private:
	Window();
	~Window();

	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;
	HINSTANCE hInstance;
	int nCmdShow;

	UINT SCREEN_WIDTH = 1280;
	UINT SCREEN_HEIGHT = 720;
	const char* APP_TITLE = "AT12B ItoDaigo";

	bool m_bFullScreen;
};

#endif // !_____WINDOW_H_____