/*
    nanogui/stackedwidget.cpp -- Widget used to stack widgets on top
    of each other. Only the active widget is visible.
*/

#include<nanogui/stactedwidget.h>

namespace nanogui {
    StackedWidget::StackedWidget(nanogui::Widget* parent) :
        Widget(parent) {}

    void StackedWidget::setSelectedIndex(int index) {
        assert(index < childCount());
        if (mSelectedIndex >= 0)
            mChildren[mSelectedIndex]->setVisible(false);
        mSelectedIndex = index;
        mChildren[mSelectedIndex]->setVisible(true);
    }

    int StackedWidget::selectedIndex() const {
        return mSelectedIndex;
    }

    void StackedWidget::performLayout(NVGcontext* ctx) {
        for (auto child : mChildren) {
            child->setPosition(Vector2i::Zero());
            child->setSize(mSize);
            child->performLayout(ctx);
        }
    }

    Vector2i StackedWidget::preferredSize(NVGcontext* ctx)const {
        Vector2i size = Vector2i::Zero();
        for (auto child : mChildren)
            size = size.cwiseMax(child->preferredSize(ctx));
        return size;
    }

    void StackedWidget::addChild(int index, Widget* widget) {
        if (mSelectedIndex >= 0)
            mChildren[mSelectedIndex]->setVisible(false);
        Widget::addChild(index, widget);
        widget->setVisible(true);
        setSelectedIndex(index);
    }

}