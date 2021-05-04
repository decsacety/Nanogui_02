#pragma once
#include<nanogui/screen.h>
#include<nanogui/window.h>
#include<nanogui/widget.h>
#include<nanogui/layout.h>
#include<nanogui/label.h>
//#include<nanogui/button.h>

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

		Label* addText(const std::string& caption) {
			Label* label = new Label(mWindow, caption, mGroupFontName, mGroupFontSize);
			if (mLayout->rowCount() > 0)
				mLayout->appendRow(mPreGroupSpacing);
			mLayout->appendRow(0);
			mLayout->setAnchor(label, AdvancedGridLayout::Anchor(0, mLayout->rowCount() - 1, 4, 1));
			mLayout->appendRow(mPostGroupSpacing);
			return label;
		}

		//Button* addButton(const std::string& label, const std::function<void()>& cb) {
		//	Button* button = new Button(mWindow, label);
		//	button->setCallback(cb);
		//	button->setFixedHeight(25);//ButtonµÄ¸ß¶È
		//	if (mLayout->rowCount() > 0)
		//		mLayout->appendRow(mVariableSpacing);
		//	mLayout->appendRow(0);
		//	mLayout->setAnchor(button, AdvancedGridLayout::Anchor(1, mLayout->rowCount() - 1, 3, 1));
		//	return button;
		//}

	protected:
		ref<Screen> mScreen;
		ref<Window> mWindow;
		ref<AdvancedGridLayout> mLayout;

		std::vector<std::function<void()>> mRefreshCallbacks;

		std::string mGroupFontName = "sans-bold";
		std::string mLabelFontName = "sans";
		Vector2i mFixedSize = Vector2i(0, 20);
		int mGroupFontSize = 12;
		int mLabelFontSize = 16;
		int mWidgetFontSize = 16;
		int mPreGroupSpacing = 5;
		int mPostGroupSpacing = 5;
		int mVariableSpacing = 5;

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}