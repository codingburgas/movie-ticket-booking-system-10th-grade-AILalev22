#pragma once
#include "window.h"
namespace Button
{
	class Button
	{
		// button pos data
		Wnd::Metrics met;
		// handle to parent window
		HWND h_wnd;
		// text displayed inside the window
		PCSTR text;
		// button window id
		int id;
	public:
		Button(PCSTR text,HWND h_wnd,Wnd::Metrics met, int id);
		~Button() = default;
		void Create();
	};
}