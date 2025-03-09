#pragma once

typedef LRESULT (CALLBACK *PPROC)(HWND, UINT, WPARAM, LPARAM);
namespace Wnd
{
	// essential window screen datas
	struct Metrics
	{
		int x;
		int y;
		int width;
		int height;
	};

	class Window
	{
		//handle to window
		HWND h_wnd;
		// position data
		Metrics met;
		// api window class
		WNDCLASS wnd_class;
	public:
		Window(HINSTANCE h_inst, Metrics met, PPROC fn, PCSTR name_cl, PCSTR name_wnd, void* l_param, PCSTR ico);
		~Window() = default;
		HWND GetHWND()
		{
			return h_wnd;
		}
	};
}