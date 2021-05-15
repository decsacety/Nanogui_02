/*
*  scr/checkbox.cpp ---Two-state check box widget
*/

#include<nanogui/checkbox.h>
#include<nanogui/theme.h>
#include<GLFW/glfw3.h>
#include<nanovg.h>

namespace nanogui {

	CheckBox::CheckBox(Widget* parent, const std::string& caption,
		const std::function<void(bool)>& callback) :
		Widget(parent), mCaption(caption), mPushed(false), mChecked(false),
		mCallback(callback) {

		mIconExtraScale = 1.2f;//Widget override
	}

	bool CheckBox::mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) {
		
		Widget::mouseButtonEvent(p, button, down, modifiers);
		if (!mEnabled)
			return false;

		if (button == GLFW_MOUSE_BUTTON_1) {
			if (down) {
				mPushed = true;
			}
			else if (mPushed) {
				if (contains(p)) {
					mChecked = !mChecked;
					if (mCallback)
						mCallback(mChecked);
				}
				mPushed = false;
			}
			return true;
		}

		return false;
	}

	Vector2i CheckBox::preferredSize(NVGcontext* ctx)const {
		if (mFixedSize != Vector2i::Zero())
			return mFixedSize;
		nvgFontSize(ctx, fontSize());
		nvgFontFace(ctx, "sans");
		return Vector2i(
			nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr) +
			1.8f * fontSize(),
			fontSize() * 1.3f);
	}


	void CheckBox::draw(NVGcontext* ctx) {
		Widget::draw(ctx);

		nvgFontSize(ctx, fontSize());
		nvgFontFace(ctx, "sans");
		nvgFillColor(ctx,
			mEnabled ? mTheme->mTextColor : mTheme->mDisabledTextColor);
		nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
		nvgText(ctx, mPos.x() + 2.f * fontSize(), mPos.y() + mSize.y() * 0.5f,
			mCaption.c_str(), nullptr);

		NVGpaint bg = nvgBoxGradient(ctx, mPos.x() + 1.5f, mPos.y() + 1.5f,
			mSize.y() - 2.0f, mSize.y() - 2.0f, 3, 3,
			mPushed ? Color(0, 100) : Color(0, 32), Color(0, 0, 0, 180));

		nvgBeginPath(ctx);
		nvgRoundedRect(ctx, mPos.x() + 1.0f, mPos.y() + 1.0f, mSize.y() - 2.0f,
			mSize.y() - 2.0f, 3);
		nvgFillPaint(ctx, bg);
		nvgFill(ctx);

		if (mChecked) {
			float tmp = (mSize.x() - mSize.x() / 1.6 + 1.f) / 2;
			tmp = tmp > 4.5f ? 3.2f : tmp;

			NVGpaint bg = nvgLinearGradient(ctx, mPos.x() + 1.5f, mPos.y() + 1.5f,
				mSize.y() - 2.f, mSize.y() - 2.f, 
				mPushed ? Color(0.26f, 0.59f, 0.98f, 0.8f) : Color(0.26f, 0.59f, 0.98f, .8f), Color(0.26f, 0.59f, 0.98f, .8f));

			nvgBeginPath(ctx);
			nvgRoundedRect(ctx, mPos.x() + tmp, mPos.y() + tmp, mSize.y()/1.6 - 1.f,
				mSize.y()/1.6 - 1.f, 0);
			nvgFillPaint(ctx, bg);
			nvgFill(ctx);

			/*nvgFontSize(ctx, mSize.y() * icon_scale());
			nvgFontFace(ctx, "icons");
			nvgFillColor(ctx, mEnabled ? mTheme -> mIconColor:mTheme->mDisabledTextColor);

			nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
			nvgText(ctx, mPos.x() + mSize.y() * .5f + 1,
				mPos.y() + mSize.y() * .5f, utf8(mTheme->mCheckBoxIcon).data(), nullptr);*/
		}


	}

}