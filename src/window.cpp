#include <glad/glad.h>
#include<nanogui/window.h>
#include<nanogui/screen.h>
#include <nanovg.h>
/*#ifdef NANOVG_GL3_IMPLEMENTATION
	#define NANOVG_GL3_IMPLEMENTATION
#endif*/
#include <nanovg_gl.h>


namespace nanogui {

	Window::Window(Widget* parent, const char* title)
		: Widget(parent), mTitle(title), mButtonPanel(nullptr),
		mModal(false), mDrag(false)
	{}

	Vector2i Window::preferredSize(NVGcontext* ctx) const{
		if (mButtonPanel)
			mButtonPanel->setVisible(false);
		Vector2i result = Widget::preferredSize(ctx);
		if (mButtonPanel)
			mButtonPanel->setVisible(true);

		nvgFontSize(ctx, 13.0f);
		nvgFontFace(ctx, "sans-bold");
		float bounds[4];
		nvgTextBounds(ctx, 0, 0, mTitle, nullptr, bounds);

		return result.cwiseMax(Vector2i(
			bounds[2] - bounds[0] + 20, bounds[3] - bounds[1] + 20
		));//y������20��Ϊ�߿�
	}

	void Window::performLayout(NVGcontext* ctx) {
		if (!mButtonPanel) {
			Widget::performLayout(ctx);
		}
		else {
			mButtonPanel->setVisible(false);
			Widget::performLayout(ctx);
			for (auto w : mButtonPanel->children()) {
				w->setFixedSize(Vector2i(22, 22));
				w->setFontSize(15);
			}
			mButtonPanel->setVisible(true);
			mButtonPanel->setSize(Vector2i(width(), 22));
			mButtonPanel->setPosition(Vector2i(width() -
				(mButtonPanel->preferredSize(ctx).x() + 5), 3));
			mButtonPanel->performLayout(ctx);
		}
	}

	void Window::draw(NVGcontext* ctx) {
		int ds = mTheme->mWindowDropShadowSize, cr = 0; //cr = mTheme->mWindowCornerRadius;
		int hh = mTheme->mWindowHeaderHeight;

		//Draw window 
		nvgSave(ctx);
		nvgBeginPath(ctx);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

		nvgFillColor(ctx, mMouseFocus ? mTheme->mWindowFillFocused
			: mTheme->mWindowFillUnfocused);
		//NVGcolor focusColor = { 0.1, 0.1, 0.2, 1 };
		//NVGcolor nfocusColor = { 0.1f, 0.2f, 0.1f,  0 };
		//nvgFillColor(ctx, (mMouseFocus ? focusColor
		//	: nfocusColor));
		nvgFill(ctx);

		//Draw a drop shadow
		NVGpaint shadowPaint = nvgBoxGradient(
			ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr * 2, ds * 2,
			mTheme->mDropShadow, mTheme->mTransparent);

		nvgSave(ctx);
		nvgResetScissor(ctx);
		nvgBeginPath(ctx);
		nvgRect(ctx, mPos.x() - ds, mPos.y() - ds, mSize.x() + 2 * ds
			, mSize.y() + 2 * ds);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(),cr);
		nvgPathWinding(ctx, NVG_HOLE);
		nvgFillPaint(ctx, shadowPaint);
		nvgFill(ctx);
		nvgRestore(ctx);

		if (mTitle) {
			NVGpaint headerPaint = nvgLinearGradient(
				ctx, mPos.x(), mPos.y(), mPos.x(), mPos.y() + hh,
				mFocused? mTheme->mWindowUnfHeaderGradientTop:mTheme->mWindowHeaderGradientTop,
				mFocused ? mTheme->mWindowUnfHeaderGradientBot:mTheme->mWindowHeaderGradientBot);

			nvgBeginPath(ctx);
			nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), hh, cr);

			nvgFillPaint(ctx, headerPaint);
			nvgFill(ctx);

			nvgBeginPath(ctx);
			nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), hh, cr);
			nvgStrokeColor(ctx, mTheme->mWindowHeaderSepTop);

			nvgSave(ctx);
			nvgIntersectScissor(ctx, mPos.x(), mPos.y(), mSize.x(), 0.5f);
			nvgStroke(ctx);
			nvgRestore(ctx);

			nvgBeginPath(ctx);
			nvgMoveTo(ctx, mPos.x() + 0.5, mPos.y() + hh - 1.5f);
			nvgLineTo(ctx, mPos.x() + mSize.x() - 0.5f, mPos.y() + hh - 1.5f);
			nvgStrokeColor(ctx, mTheme->mWindowHeaderSepBot);
			nvgStroke(ctx);

			nvgFontSize(ctx, 13.0f);
			nvgFontFace(ctx, "sans-bold");
			nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

			nvgFontBlur(ctx, 2);
			nvgFillColor(ctx, mTheme->mDropShadow);
			nvgText(ctx, mPos.x() + mSize.x() / 2,
				mPos.y() + hh / 2, mTitle, nullptr);

			nvgFontBlur(ctx, 0);
			nvgFillColor(ctx, mFocused ? mTheme->mWindowTitleFocused :
				mTheme->mWindowTitleUnfocused);
			nvgText(ctx, mPos.x() + mSize.x() / 2, mPos.y() + hh / 2 - 1,
				mTitle, nullptr);

		}

		nvgRestore(ctx);
		Widget::draw(ctx);


	}

	void Window::refreshRelativePlacement() {
		//override by popued  
	}

	bool Window::mouseDragEvent(const Vector2i& p, const Vector2i& rel,
		int button, int /*modifiers*/) {
		if (mDrag && (button & (1 << GLFW_MOUSE_BUTTON_1)) != 0) {
			mPos += rel;
			mPos = mPos.cwiseMax(Vector2i::Zero());
			mPos = mPos.cwiseMin(parent()->size() - mSize);
			return true;
		}
		if (button == GLFW_MOUSE_BUTTON_3) {
			mSize +=rel;

			mSize.x() = mSize.x() < MinSubWindowSize.x() ?  MinSubWindowSize.x() : mSize.x();
			mSize.y() = mSize.y() < MinSubWindowSize.y() ? MinSubWindowSize.y() : mSize.y();
			return true;
		}
		return false;
	}

	bool Window::mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) {
		if (Widget::mouseButtonEvent(p, button, down, modifiers))
			return true;
		if (button == GLFW_MOUSE_BUTTON_1 || button == GLFW_MOUSE_BUTTON_2) {
			mDrag = down && (p.y() - mPos.y()) < mTheme->mWindowHeaderHeight;
			return true;
		}
		return false;
	}
}