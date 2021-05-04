#include<nanogui/button.h>
#include<nanovg.h>
#include<nanogui/theme.h>

namespace nanogui {

	Button::Button(Widget *parent, const std::string &caption, int icon)
		:Widget(parent), mCaption(caption), mIcon(icon),
		mIconPosition(IconPosition::LeftCentered), mPushed(false),
		mFlags(NormalButton), mBackgroundColor(Color(0,0)),
		mTextColor (Color(0,0)){}

	Vector2i Button::preferredSize(NVGcontext* ctx) const {
		int fontSize = mFontSize == -1 ? mTheme->mButtonFontSize : mFontSize;
		nvgFontSize(ctx, fontSize);
		nvgFontFace(ctx, "sans-bold");
		float tw = nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr);
		float iw = 0.0f, ih = fontSize;

		if (mIcon) {
			if (nvgIsFontIcon(mIcon)) {
				//ih *= icon_scale();
				//nvgFontSize(ctx, "icons");
			}
		}

		return Vector2i(0, 0);
	}

	bool Button::mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) {
		return false;
	}

	void Button::draw(NVGcontext* ctx) {

	}
}