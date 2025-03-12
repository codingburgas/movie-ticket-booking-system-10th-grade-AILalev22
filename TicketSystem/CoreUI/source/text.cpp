#include "pch.h"

#include "text.h"
namespace Text
{	
	void Label(PCSTR text, int id, HWND h_wnd, Wnd::Metrics met)
	{
		CreateWindow("Static", text, WS_VISIBLE | WS_CHILD, met.x, met.y, met.width, met.height, h_wnd, (HMENU)id, NULL, NULL);
	}
	void Print(HDC hdc,PCSTR text, int x, int y)
	{
		TextOut(hdc, x, y, text, Str::Len(text));
	}

	Input::Input(HWND h_wnd, Wnd::Metrics met) : h_input(0),met(met),h_wnd(h_wnd)
	{
		Mem::Set(buffer, 0, sizeof(buffer));
	}
	PCSTR Input::GetInput()
	{
		int len = GetWindowText(h_input, buffer, sizeof(buffer));
		buffer[len] = 0;
		return buffer;
	}
	void Input::Create()
	{
		if(!h_input)
		h_input = CreateWindow("Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE,met.x,met.y,met.width,met.height, h_wnd,0, 0, 0);
	}
}