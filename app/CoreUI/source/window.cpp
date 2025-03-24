#include "pch.h"
#include "window.h"

namespace Wnd
{
	Window::Window(HINSTANCE h_inst, Metrics met, PPROC fn, PCSTR name_cl, PCSTR name_wnd, void* l_param, PCSTR ico)
	{
		this->met = met;

		wnd_class = {};
		wnd_class.lpszClassName = name_cl;
		wnd_class.lpfnWndProc = fn;
		wnd_class.hInstance = h_inst;
		wnd_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		wnd_class.hIcon = (HICON)LoadIcon(ico ? h_inst : NULL, ico ? ico : IDI_APPLICATION);
		RegisterClass(&wnd_class);

		h_wnd = CreateWindowEx(0,name_cl, name_wnd,WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, met.x, met.y, met.width, met.height, 0, 0,h_inst, l_param);
	}
}
