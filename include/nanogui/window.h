#pragma once
#include<nanogui/common.h>
#include<nanogui/widget.h>
#include<iostream>

namespace nanogui {
	NANOGUI_EXPORT class Window :public Widget{
	public:
		NANOGUI_EXPORT Window(Widget* parent, const char* title = "Untitle");
		const std::string title() const { std::string l = mTitle; return l; }
	protected:
		const char* mTitle;
		Widget* mButtonPanel;
		bool mModal;
		bool mDrag;
	};
}