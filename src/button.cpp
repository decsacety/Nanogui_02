#include<nanogui/button.h>
#include<nanovg.h>
#include<nanogui/theme.h>
#include <GLFW/glfw3.h>

namespace nanogui {

	Button::Button(Widget *parent, const std::string &caption, int icon, const std::string& appendixText)
		:Widget(parent), mCaption(caption), mAppendixText(appendixText) , mIcon(icon),
		mIconPosition(IconPosition::LeftCentered), mPushed(false),
		mFlags(NormalButton), mBackgroundColor(Color(0,0)),
		mTextColor (Color(0,0)){
		mLeftMargin = -1;
		mShortButton = false;
		mTextLeftMargin = 0;
	}

	Vector2i Button::preferredSize(NVGcontext* ctx) const {
		int fontSize = mFontSize == -1 ? mTheme->mButtonFontSize : mFontSize;
		nvgFontSize(ctx, fontSize);
		nvgFontFace(ctx, "sans-bold");
		float tw = nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr);
		float iw = 0.0f, ih = fontSize;

		if (mIcon) {
			if (nvgIsFontIcon(mIcon)) {
				ih *= icon_scale();
				nvgFontFace(ctx, "icons");
				nvgFontSize(ctx, ih);
				iw = nvgTextBounds(ctx, 0, 0, utf8(mIcon).data(), nullptr, nullptr)
					+mSize.y() *0.15f;
			}
			else {
				int w, h;
				ih *= 0.9f;
				nvgImageSize(ctx, mIcon, &w, &h);
				iw = w * ih / h;
			}
		}

		return Vector2i((int)(tw + iw) + 20, fontSize + 10);
	}

	bool Button::mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) {
		Widget::mouseButtonEvent(p, button, down, modifiers);

		ref<Button> self = this;

		if (button == GLFW_MOUSE_BUTTON_1 && mEnabled) {
			bool pushedBackup = mPushed;
			if (down) {
				if (mFlags & RadioButton) {
					if (mButtonGroup.empty()) {
						for (auto widget : parent()->children()) {
							Button* b = dynamic_cast<Button*>(widget);
							if (b != this && b && (b->flags() & RadioButton) && b->mPushed) {
								b->mPushed = false;
								if (b->mChangeCallback)
									b->mChangeCallback(false);
							}
						}
					}
					else{
						for (auto b : mButtonGroup) {
							if (b != this && (b->flags() & RadioButton) && b->mPushed) {
								b->mPushed = false;
								if (b->mChangeCallback)
									b->mChangeCallback(false);
							}
						}
					}
				}

				if (mFlags & PopupButton) {
					for (auto widget : parent()->children()) {
						Button* b = dynamic_cast<Button*>(widget);
						if (b != this && b && (b->flags() & PopupButton) && b->mPushed) {
							b->mPushed = false;
							if (b->mChangeCallback)
								b->mChangeCallback(false);
						}
					}
				}
				if (mFlags & ToggleButton)
					mPushed = !mPushed;
				else
					mPushed = true;
			}
			else if (mPushed) {
				if (contains(p) && mCallback)
					mCallback();
				if (mFlags & NormalButton)
					mPushed = false;
			}
			if (pushedBackup != mPushed && mChangeCallback)
				mChangeCallback(mPushed);

			return true;
		}

		return false;
	}

	void Button::draw(NVGcontext* ctx) {
		Widget::draw(ctx);

		NVGcolor gradTop = mTheme->mButtonGradientTopUnfocused;
		NVGcolor gradBot = mTheme->mButtonGradientBotUnfocused;

		if (mPushed) {
			gradTop = mTheme->mButtonGradientTopPushed;
			gradBot = mTheme->mButtonGradientBotPushed;
		}
		else if (mMouseFocus && mEnabled) {
			gradTop = mTheme->mButtonGradientTopFocused;
			gradBot = mTheme->mButtonGradientBotFocused;
		}

		nvgBeginPath(ctx);

		nvgRoundedRect(ctx, mPos.x() + 1, mPos.y() + 1.0f, mSize.x() - 2,
			mSize.y() - 2, mTheme->mButtonCornerRadius - 1);

		if (mBackgroundColor.w() != 0) {
			nvgFillColor(ctx, Color(mBackgroundColor.head<3>(), 1.f));
			nvgFill(ctx);
			if (mPushed) {
				gradTop.a = gradBot.a = 0.8f;
			}
			else {
				double v = 1 - mBackgroundColor.w();
				gradTop.a = gradBot.a = mEnabled ? v : v * .5f + .5f;
			}
		}

		NVGpaint bg = nvgLinearGradient(ctx, mPos.x(), mPos.y(), mPos.x(),
			mPos.y() + mSize.y(), gradTop, gradBot);

		if(mLeftMargin!=-1)
			mPos.x() = mLeftMargin;//距离左侧边界统一设定自定义距离。
		if (mCaption.size() <= 8)
			mSize.x() = 60;
		else
			mSize.x() = mCaption.size() * 7.8;//设定button宽度，每个字符8个像素，
		if (mShortButton)
			mSize.x() = mWidth;
		mSize.y() = mTheme->mButtonFontSize * 1.6;//设定button高度，为字体大小的1.4倍

		nvgFillPaint(ctx, bg);
		nvgFill(ctx);

		////button 上下边缘光
		//nvgBeginPath(ctx);
		//nvgStrokeWidth(ctx, 1.0f);
		//nvgRoundedRect(ctx, mPos.x() + 0.5f, mPos.y() + (mPushed ? 0.5f : 1.5f), mSize.x() - 1,
		//	mSize.y() - 1 - (mPushed ? 0.0f : 1.0f), 0);//原为mTheme->mButtonCornerRadius，设定为0取直角
		//nvgStrokeColor(ctx, mTheme->mBorderLight);
		//nvgStroke(ctx);

		//button环绕边缘阴影
		nvgBeginPath(ctx);
		nvgRoundedRect(ctx, mPos.x() + 0.5f, mPos.y() + .5f, mSize.x() - 1,
			mSize.y() - 2, 0);//mTheme->mButtonCornerRadius
		nvgStrokeColor(ctx, mTheme->mBorderDark);
		nvgStroke(ctx);

		int fontSize = mFontSize == -1 ? mTheme->mButtonFontSize : mFontSize;
		nvgFontSize(ctx, fontSize);
		nvgFontFace(ctx, "sans-bold");
		float tw = nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr);

		Vector2f center = mPos.cast<float>() + mSize.cast<float>() * 0.5f;
		Vector2i textPos(center.x() - tw * 0.5f, center.y() - 1);
		NVGcolor textColor =
			mTextColor.w() == 0 ? mTheme->mTextColor : mTextColor;
		if (!mEnabled)
			textColor = mTheme->mDisabledTextColor;

		if (mIcon) {
			auto icon = utf8(mIcon);

			float iw, ih = fontSize;
			if (nvgIsFontIcon(mIcon)) {
				ih *= icon_scale();
				nvgFontSize(ctx, ih);
				nvgFontFace(ctx, "icons");
				iw = nvgTextBounds(ctx, 0, 0, icon.data(), nullptr, nullptr);
			}
			else {
				int w, h;
				ih *= 0.9f;
				nvgImageSize(ctx, mIcon, &w, &h);
				iw = w * ih / h;
			}

			if(mCaption != "")
				iw+=mSize.y()*0.15f;
			nvgFillColor(ctx, textColor);
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
			Vector2f iconPos = center;
			iconPos.y() -= 1;

			if (mIconPosition == IconPosition::LeftCentered) {
				iconPos.x() -= (tw + iw) * 0.5;
				textPos.x() += iw * 0.5f;
			}
			else if (mIconPosition == IconPosition::RightCentered) {
				textPos.x() -= iw * 0.5f;
				iconPos.x() += tw * 0.5f;
			}
			else if (mIconPosition == IconPosition::Left) {
				iconPos.x() = mPos.x() + 8;
			}
			else if (mIconPosition == IconPosition::Right) {
				iconPos.x() = mPos.x() + mSize.x() - iw - 8;
			}

			if (nvgIsFontIcon(mIcon)) {
				nvgText(ctx, iconPos.x(), iconPos.y() + 1, icon.data(), nullptr);
			}
			else {
				NVGpaint imgPaint = nvgImagePattern(ctx,
					iconPos.x(), iconPos.y() - ih / 2, iw, ih, 0, mIcon, mEnabled ? 0.5f : 0.25f);
				nvgFillPaint(ctx, imgPaint);
				nvgFill(ctx);
			}

		}

		nvgFontSize(ctx, fontSize);
		nvgFontFace(ctx, "sans-bold");
		nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
		nvgFillColor(ctx, mTheme->mTextColorShadow);
		nvgText(ctx, mTextLeftMargin ? mTextLeftMargin:textPos.x(), textPos.y()+1, mCaption.c_str(), nullptr);
		nvgFillColor(ctx, textColor);
		nvgText(ctx, mTextLeftMargin ? mTextLeftMargin : textPos.x(), textPos.y() + 2, mCaption.c_str(), nullptr);


		if (mAppendixText != "") {
			nvgRestore(ctx);
			nvgSave(ctx);
			nvgIntersectScissor(ctx, mPos.x(), mPos.y(), mSize.x() + 15+mAppendixText.size()* 8, mSize.y());//size+80来扩展绘制范围

			nvgFontSize(ctx, fontSize);
			nvgFontFace(ctx, "sans-bold");
			nvgFillColor(ctx, textColor);
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
			nvgText(ctx, textPos.x() + mSize.x() +5, textPos.y()-3, mAppendixText.c_str(), nullptr);
		}

	}
}