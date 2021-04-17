#include<nanogui/window.h>
#include<nanogui/screen.h>

namespace nanogui {

	Window::Window(Widget* parent, const char* title)
		: Widget(parent), mTitle(title), mButtonPanel(nullptr),
		mModal(false), mDrag(false)
	{}
}