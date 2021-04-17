#include<nanogui/widget.h>

namespace nanogui {
	Widget::Widget(Widget * parent): mParent(nullptr),mTheme(nullptr){
		if (parent)
			parent->addChild(this);
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
}