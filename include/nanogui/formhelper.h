#pragma once
#include<nanogui/screen.h>
#include<nanogui/window.h>
#include<nanogui/widget.h>
#include<nanogui/layout.h>

namespace nanogui {
	class FormHelper {
	public:  
		FormHelper(Screen* screen){
			mScreen = screen;
		}

		Window* addWindow(Vector2i pos , const char* title = "NoName")
		{
			mWindow = new Window(mScreen, title);
			mLayout = new AdvancedGridLayout({ 10,0,10,0 }, {});
			mLayout->setMargin(0);
			mLayout->setColStretch(2, 1);
			mWindow->setPosition(pos);
			mWindow->setLayout(mLayout);
			mWindow->setVisible(true);
			return mWindow;
		}
	protected:
		ref<Screen> mScreen;
		ref<Window> mWindow;
		ref<AdvancedGridLayout> mLayout;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}