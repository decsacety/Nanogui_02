#pragma once
#include<nanogui/common.h>
#include<nanogui/widget.h>

namespace nanogui {
	NANOGUI_EXPORT class Window :public Widget{
	public:
		Window(Widget* parent, const char* title);
	
	protected:
		const char* mTitle;
		Widget* mButtonPanel;
		bool mModal;
		bool mDrag;
	};
}