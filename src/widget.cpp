#include<nanogui/widget.h>
#include<GLFW/glfw3.h>
#include<nanogui/screen.h>
#include<nanovg.h>
#include <iostream>

namespace nanogui {
	Widget::Widget(Widget * parent) : mParent(nullptr), mTheme(nullptr), mLayout(nullptr),
		mPos(Vector2i::Zero()), mSize(Vector2i::Zero()),
		mFixedSize(Vector2i::Zero()), mVisible(true), mEnabled(true),
		mFocused(false), mMouseFocus(false), mTooltip(""), mFontSize(-1.0f),
		mIconExtraScale(1.0f), mCursor(Cursor::Arrow) {
		if (parent)
			parent->addChild(this);

		MinSubWindowSize = Vector2i(20, 20);
	}

	Widget::~Widget() {
		for (auto child : mChildren) {
			if (child)
				child->decRef();
		}
	}

	void Widget::addChild(Widget* widget) {
		addChild(childCount(), widget);
	}
	void Widget::addChild(int index, Widget* widget) {
		mChildren.insert(mChildren.begin() + index, widget);
		widget->incRef();
		widget->setParent(this);
		widget->setTheme(mTheme);
	}
	void Widget::setTheme(Theme* theme) {
		if (mTheme.get() == theme)
			return;
		mTheme = theme;
		for (auto child : mChildren)
			child->setTheme(theme);
	}

	int Widget::fontSize() const {
		return (mFontSize < 0 && mTheme) ? mTheme->mStandardFontSize : mFontSize;
	}

	Vector2i Widget::preferredSize(NVGcontext* ctx) const {
		if (mLayout)
			return mLayout->preferredSize(ctx, this);
		else
			return mSize;
	}

	void Widget::performLayout(NVGcontext* ctx) {
		if (mLayout) {
			mLayout->performLayout(ctx, this);
		}
		else {
			for (auto c : mChildren) {
				Vector2i pref = c->preferredSize(ctx), fix = c->fixedSize();
				c->setSize(Vector2i(
					fix[0] ? fix[0] : pref[0],
					fix[1] ? fix[1] : pref[1]
				));
				c->performLayout(ctx);
			}
		}
	}

	Widget* Widget::findWidget(const Vector2i& p) {
		for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
			Widget* child = *it;
			if (child->visible() && child->contains(p - mPos))
				return child->findWidget(p - mPos);
		}
		return contains(p) ? this : nullptr;
	}

	void Widget::requestFocus() {
		Widget* widget = this;
		while (widget->parent())
			widget = widget->parent();
		((Screen*)widget)->updateFocus(this);
	}

	void Widget::draw(NVGcontext* ctx) {
		if (mChildren.empty())
			return;

		nvgSave(ctx);
		nvgTranslate(ctx, mPos.x(), mPos.y());
		for (auto child : mChildren) {
			if (child->visible()) {
				nvgSave(ctx);
				nvgIntersectScissor(ctx, child->mPos.x(), child->mPos.y(), child->mSize.x()+80, child->mSize.y());//size+80À´À©Õ¹»æÖÆ·¶Î§
				child->draw(ctx);
				nvgRestore(ctx);
			}
		}
		nvgRestore(ctx);
	}

	bool Widget::mouseDragEvent(const Vector2i&, const Vector2i&, int, int) {
		return false;
	}

	bool Widget::keyboardEvent(int, int, int, int) {
		return false;
	}

	bool Widget::keyboardCharacterEvent(unsigned int codepoint) {
		return false;
	}

	bool Widget::mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) {
		for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
			Widget* child = *it;
			if (child->visible() && child->contains(p - mPos) &&
				child->mouseButtonEvent(p - mPos, button, down, modifiers))
				return true;
		}
		if ((button == GLFW_MOUSE_BUTTON_1 || button == GLFW_MOUSE_BUTTON_2)  && down && !mFocused)
			requestFocus();
		return false;
	}

	bool Widget::mouseMotionEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) {
		for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
			Widget* child = *it;
			if (!child->visible())
				continue;
			bool contained = child->contains(p - mPos), prevContained = child->contains(p - mPos - rel);
			if (contained != prevContained)
				child->mouseEnterEvent(p, contained);
			if ((contained || prevContained) &&
				child->mouseMotionEvent(p - mPos, rel, button, modifiers))
				return true;
		}
		return false;
	}

	bool Widget::scrollEvent(const Vector2i& p, const Eigen::Vector2f &rel) {
		for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it) {
			Widget* child = *it;
			if (!child->visible())
				continue;
			if (child->contains(p - mPos) && child->scrollEvent(p - mPos, rel))
				return true;
		}
		return false;
	}

	bool Widget::mouseEnterEvent(const Vector2i&, bool enter) {
		mMouseFocus = enter;
		return false;
	}

	bool Widget::focusEvent(bool focused) {
		mFocused = focused;
		return false;
	}
	

}