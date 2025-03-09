#include <string.h>
#include <wchar.h>
#include <windows.h>
#include "core.h"
#include "window.h"
#include "menu.h"
#include "text.h"
#include "Resource.h"
#include <new.h>
#include "button.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define MAX_WIDTH 960
#define MAX_HEIGHT 540
#define MIN_WIDTH MAX_WIDTH
#define MIN_HEIGHT MAX_HEIGHT
#define BUTTON_ID 4
void addControls(HWND);
void addMenus(HWND);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR cmdLine, int nCmdShow)
{
	Core::Init();
	Wnd::Metrics mWindow;
	mWindow.width = 960;
	mWindow.height = 540;
	mWindow.x = (GetSystemMetrics(SM_CXSCREEN) - mWindow.width) / 2;
	mWindow.y = (GetSystemMetrics(SM_CYSCREEN) - mWindow.height) / 2;

	void* memoryWnd = (char*)Mem::Alloc(sizeof(Wnd::Window));
	Wnd::Window* wnd = new (memoryWnd) Wnd::Window(hInstance, mWindow, WndProc, "ClassWindow", "TicketSystem", 0, MAKEINTRESOURCE(IDI_TICKET));
	
	ShowWindow(wnd->GetHWND(), nCmdShow);
	UpdateWindow(wnd->GetHWND());

	MSG msg = {};
	while (GetMessage(&msg, wnd->GetHWND(), 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	wnd->~Window();
	Mem::Free(memoryWnd);
	Core::Release();
	Menu::Release();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static Text::Input i(hwnd, { 30,30,100,100 });
    static bool p = 0;
    switch (uMsg)
    {
    case WM_CREATE:
        addMenus(hwnd);
        addControls(hwnd);
        i.Create();
        return 0;

    case WM_SIZING:
    {
        RECT* rect = (RECT*)lParam;
        if (rect->right - rect->left < MIN_WIDTH)
            rect->right = rect->left + MIN_WIDTH;

        if (rect->right - rect->left > MAX_WIDTH)
            rect->right = rect->left + MAX_WIDTH;

        if (rect->bottom - rect->top < MIN_HEIGHT)
            rect->bottom = rect->top + MIN_HEIGHT;

        if (rect->bottom - rect->top > MAX_HEIGHT)
            rect->bottom = rect->top + MAX_HEIGHT;

        return 0;
    }

    case WM_COMMAND:
        switch (wParam)
        {
        case BUTTON_ID:
            // Trigger a repaint by invalidating the window to make sure WM_PAINT is called
            InvalidateRect(hwnd, NULL, TRUE);  // This will cause WM_PAINT to be sent
            p = 1;

            return 0;
        }
        return 0;

    case WM_PAINT:
    {
        // Handle the paint message and draw on the window
        hdc = BeginPaint(hwnd, &ps);

        // Example of printing text when the button is clicked
        if(p)
        Text::Print(hdc, "WELCOME", 50, 50);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
void addMenus(HWND hwnd)
{
    Menu::Init();
    Menu::Menu mShow("Show", 0);
    mShow.Create();
    mShow.AppendOpt("open", 9);
    mShow.AppendSep();
    mShow.AppendOpt("close", 99);
    Menu::SetHandle(hwnd, 0);
    //Menu::Release();
}
void addControls(HWND hwnd)
{
    Text::Label("Enter pass here:", 0, hwnd, { 300, 300, 110, 20 });
    Button::Button b("Print", hwnd, { 60,60,60,60 }, BUTTON_ID);
    b.Create();
}