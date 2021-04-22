#include<glad/glad.h>
#include<nanogui/popup.h>
#include<nanogui/widget.h>
#include<nanogui/theme.h>
#include <nanovg.h>

namespace nanogui {
	Popup::Popup(Widget *parent ,Window *parentWindow):
		Window(parent, ""), mParentWindow(parentWindow),
		mAnchorPos(Vector2i::Zero()), mAnchorHeight(30),mSide(Side::Right){
	}

	void Popup::performLayout(NVGcontext* ctx) {
		if (mLayout || mChildren.size() != 1) {
			Widget::performLayout(ctx);
		}
		else {
			mChildren[0]->setPosition(Vector2i::Zero());
			mChildren[0]->setSize(mSize);
			mChildren[0]->performLayout(ctx);
		}
		if (mSide == Side::Left)
			mAnchorPos[0] -= size()[0];
	}

	void Popup::refreshRelativePlacement() {
		mParentWindow->refreshRelativePlacement();
		mVisible &= mParentWindow->visibleRecursive();
	}

	void Popup::draw(NVGcontext* ctx) {
		refreshRelativePlacement();

		if (!mVisible)
			return;
		int ds = mTheme->mWindowDropShadowSize, cr = mTheme->mWindowCornerRadius;

		nvgSave(ctx);
		nvgResetScissor(ctx);

		//Draw Shadow
		NVGpaint shadowPaint = nvgBoxGradient(
			ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr * 2, ds * 2,
			mTheme->mDropShadow, mTheme->mTransparent);

		nvgBeginPath(ctx);
		nvgRect(ctx, mPos.x() - ds, mPos.y() - ds, mSize.x() + 2 * ds, mSize.y() + 2 * ds);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);
		nvgPathWinding(ctx, NVG_HOLE);
		nvgFillPaint(ctx, shadowPaint);
		nvgFill(ctx);

		//Draw window
		nvgBeginPath(ctx);
		nvgRoundedRect(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y(), cr);

		Vector2i base = mPos + Vector2i(0, mAnchorHeight);
		int sign = -1;
		if (mSide == Side::Left) {
			base.x() += mSize.x();
			sign = 1;
		}

		nvgMoveTo(ctx, base.x() + 15 * sign, base.y());
		nvgLineTo(ctx, base.x() - 1 * sign, base.x() - 15);
		nvgLineTo(ctx, base.x() - 1 * sign, base.y() + 15);

		nvgFillColor(ctx, mTheme->mWindowPopup);
		nvgFill(ctx);
		nvgRestore(ctx);

		Widget::draw(ctx);

	}

}