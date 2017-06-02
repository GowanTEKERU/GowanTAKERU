#include"Render.h"
#include"Control.h"
#include"Player.h"

#define TITLE 	TEXT("Basic of game")

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);

}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX Wndclass;
	Wndclass.cbSize = sizeof(WNDCLASSEX);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = NULL;
	Wndclass.hCursor = NULL;
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TITLE;
	Wndclass.hIconSm = NULL;

	//Window�̓o�^
	RegisterClassEx(&Wndclass);

	//Window�̐���
	HWND hWnd = CreateWindow(
		TITLE,								//�E�B���h�E�̃N���X��
		"TITLE", 							//�E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		DISPLAY_WIDTH,							// Width�i���j
		DISPLAY_HEIGHT,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
	);
	SetProcessDPIAware();					//�����

	/*-------------------------------------------
	resize
	-------------------------------------------*/
	/*RECT RectWnd;
	RECT RectCli;
	int cx = 0;
	int cy = 0;
	GetWindowRect(hWnd, &RectWnd);
	GetClientRect(hWnd, &RectCli);
	cx = RectWnd.right - RectCli.right;
	cy = RectWnd.bottom - RectCli.bottom;
	SetWindowPos(hWnd, NULL, NULL, NULL, RectCli.right + cx, RectCli.bottom + cy, SWP_NOMOVE);*/

	//direct graphics������
	bool fullscreen = true;
	DXGraphicsInit(hWnd, fullscreen);
	TextureInit();

	//direct input������
	DXInputKeybourdInit(hWnd, hInstance);
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	DWORD oldtime = timeGetTime();
	DWORD currenttime;

	PlayerInit();

	timeBeginPeriod(1);

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != false) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			currenttime = timeGetTime();
			if (currenttime - oldtime >= 1000 / 60) {
				oldtime = currenttime;

				/*Contorol();*/
				Render();

			}
			else {
				Sleep(1);
			}
		}
		timeEndPeriod(1);
	}

	FreeDxInput();
	FreeDxGraphics();

	return (int)msg.wParam;
}