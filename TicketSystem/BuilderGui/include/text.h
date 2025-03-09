#pragma once
#include "window.h"
#include "string.hpp"
namespace Text
{
	// create a label on a parent window
	void Label(PCSTR text, int id, HWND h_wnd, Wnd::Metrics met);
	// TextOut with self calculating len
	void Print(HDC hdc,PCSTR text, int x, int y);

	class Input
	{
		// handle to parent window
		HWND h_wnd;
		// handle to input window
		HWND h_input;
		// buffer where input is stored
		char buffer[100];
		// input window pos data
		Wnd::Metrics met;
	public:
		Input(HWND h_wnd, Wnd::Metrics met);
		~Input() = default;
		// return text from input field
		PCSTR GetInput();
		// create the input window
		void Create();
	};
}