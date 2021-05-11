/*
* src/coloerpicker.cpp
*/

#include<nanogui/colorpicker.h>
#include<nanogui/layout.h>
#include<nanogui/colorwheel.h>

namespace nanogui {

	ColorPicker::ColorPicker(Widget* parent, const Color& color) : PopupButton(parent, "") {
		setBackgroundColor(color);
		Popup* popup = this->popup();
		popup->setLayout(new GroupLayout());

		//initialize callback to do nothing: this is for users to hook into 
		//receiving a new color value
		mCallback = [](const Color&) {};
		mFinalCallback = [](const Color&) {};

		//set the color wheel to the specified color
		mColorWheel = new ColorWheel(popup, color);

		//set the pick button to the specifired color
		mPickButton = new Button(popup, "Pick");
		mPickButton->setBackgroundColor(color);
		mPickButton->setTextColor(color.contrastingColor());
		mPickButton->setFixedSize(Vector2i(100, 20));

		//set tje reset button to the specified color
		mResetButton = new Button(popup, "Reset");
		mResetButton->setBackgroundColor(color);
		mResetButton->setTextColor(color.contrastingColor());
		mResetButton->setFixedSize(Vector2i(100, 20));

		PopupButton::setChangeCallback([&](bool) {
			if (this->mPickButton->pushed()) {
				setColor(backgroundColor());
				mFinalCallback(backgroundColor());
			}
		});

		mColorWheel->setCallback([&](const Color& value) {
			mPickButton->setBackgroundColor(value);
			mPickButton->setTextColor(value.contrastingColor());
			mCallback(value);
		});

		mPickButton->setCallback([this]() {
			if (mPushed) {
				Color value = mColorWheel->color();
				setPushed(false);
				setColor(value);
				mFinalCallback(value);
			}
		});

		mResetButton->setCallback([this]() {
			Color bg = this->mResetButton->backgroundColor();
			Color fg = this->mResetButton->textColor();

			mColorWheel->setColor(bg);
			mPickButton->setBackgroundColor(bg);
			mPickButton->setTextColor(fg);

			mCallback(bg);
			mFinalCallback(bg);
		});

	}

	Color ColorPicker::color() const {
		return backgroundColor();
	}

	void ColorPicker::setColor(const Color& color) {
		/*Ignore setColor() calls when the user is currently editing*/
		if (!mPushed)
		{
			Color fg = color.contrastingColor();
			setBackgroundColor(color);
			setTextColor(fg);
			mColorWheel->setColor(color);

			mPickButton->setBackgroundColor(color);
			mPickButton->setTextColor(fg);

			mResetButton->setBackgroundColor(color);
			mResetButton->setTextColor(fg);
		}

	}

}