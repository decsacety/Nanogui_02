//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <nanovg.h>
#include <nanogui/label.h>
#include <nanogui/theme.h>

namespace nanogui {

	Label::Label(Widget* parent, const std::string& caption, const std::string& font,
		int fontSize) :Widget(parent), mCaption(caption), mFont(font)
	{
		if (mTheme) {
			mFontSize = mTheme->mStandardFontSize;
			mColor = mTheme->mTextColor;
		}
		if (fontSize >= 0) mFontSize = fontSize;

		leftMargin = -1;//�趨Ϊ-1��ʾʹ��Ĭ�Ͼ��롣
	}

	void Label::setTheme(Theme* theme) {
		Widget::setTheme(theme);
		if (mTheme) {
			mFontSize = mTheme->mStandardFontSize;
			mColor = mTheme->mTextColor;
		}
	}

	Vector2i Label::preferredSize(NVGcontext* ctx) const {
		if (mCaption == "")
			return Vector2i::Zero();
		nvgFontFace(ctx, mFont.c_str());
		nvgFontSize(ctx, fontSize());
		if (mFixedSize.x() > 0) {
			float bounds[4];
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
			nvgTextBoxBounds(ctx, mPos.x(), mPos.y(), mFixedSize.x(), mCaption.c_str(),
				nullptr, bounds);
			return Vector2i(mFixedSize.x(), bounds[3] - bounds[1]);
		}
		else {
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
			return Vector2i(
				nvgTextBounds(ctx, 0, 0, mCaption.c_str(), nullptr, nullptr) + 2,
				fontSize()
			);
		}

	}

	void Label::draw(NVGcontext* ctx) {
		Widget::draw(ctx);
		nvgFontFace(ctx, mFont.c_str());
		nvgFontSize(ctx, fontSize());
		nvgFillColor(ctx, mColor);

		if (leftMargin != -1)/*�����Ϊ-1�����ֶ������˾���*/ {
			nvgRestore(ctx);
			nvgSave(ctx);
			mPos.x() = leftMargin;//�趨��߽�
			nvgFontSize(ctx, fontSize());//�����趨fontSize 
			nvgIntersectScissor(ctx, leftMargin, mPos.y(), mSize.x(), mSize.y());//�޸Ļ��ؼ��ķ�Χ
		}

		if (mFixedSize.x() > 0) {
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
			nvgTextBox(ctx, mPos.x(), mPos.y(), mFixedSize.x(), mCaption.c_str(), nullptr);
		}
		else {
			nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
			nvgText(ctx, mPos.x(), mPos.y() + mSize.y() * 0.5f, mCaption.c_str(), nullptr);
		}
	}

}