#include "pch.h"
#include "button.h"


namespace Button
{
	Button::Button(PCSTR text, HWND h_wnd, Wnd::Metrics met,int id) : text(text),h_wnd(h_wnd),met(met),id(id)
	{

	}
	void Button::Create()
	{
		CreateWindow("Button", text, WS_VISIBLE | WS_CHILD, met.x, met.y, met.width, met.height, h_wnd, (HMENU)id, 0, 0);
	}
}