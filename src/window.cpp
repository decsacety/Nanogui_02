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

		nvgFontSize(ctx, 18.0f);
		nvgFontFace(ctx, "sans-bold");
		float bounds[4];
		nvgTextBounds(ctx, 0, 0, mTitle, nullptr, bounds);

		return result.cwiseMax(Vector2i(bounds[2] - bounds[0] + 20, bounds[3] - bounds[1]));
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
		int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;
		int hh = mTheme->mWindowHeaderHeight;

		nvgSave(ctx);
		nvgBeginPath(ctx);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(),mSize.y(), cr);

		/*nvgFillColor(ctx, mMouseFocus ? mTheme->mWindowFillFocused
			: mTheme->mWindowFillUnfocused);*/
		NVGcolor focusColor = { 0.1, 0.1, 0.2, 1.0f };
		NVGcolor nfocusColor = { 0.1f, 0.2f, 0.1f, 1.0f };
		nvgFillColor(ctx, (mMouseFocus ? focusColor
			: nfocusColor));
		nvgFill(ctx);

		////Draw a drop shadow
		//NVGpaint shadowPaint = nvgBoxGradient(
		//	ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr * 2, ds * 2,
		//	mTheme->mWindowDropShadowSize, mTheme->mTransparent);

		nvgSave(ctx);
		nvgResetScissor(ctx);
		nvgBeginPath(ctx);
		nvgRect(ctx, mPos.x() - ds, mPos.y() - ds, mSize.x() + 2 * ds
			, mSize.y() + 2 * ds);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(),cr);
		nvgPathWinding(ctx, NVG_HOLE);
		nvgFill(ctx);
		nvgRestore(ctx);

		nvgRestore(ctx);
		Widget::draw(ctx);


	}

	void Window::refreshRelativePlacement() {
		//override by popued  
	}

}