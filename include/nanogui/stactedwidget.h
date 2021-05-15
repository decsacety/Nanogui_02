/*
    nanogui/stackedwidget.h -- Widget used to stack widgets on top
    of each other. Only the active widget is visible.
*/

#pragma once

#include<nanogui/widget.h>

namespace nanogui {

    /*
    * \class StackedWidget stackedWidget.h nanogui/stackedwidget.h
    * 
    * \brief A stack widget
    */

    class NANOGUI_EXPORT StackedWidget :public Widget {
    public:
        StackedWidget(Widget* parent);

        void setSelectedIndex(int index);
        int selectedIndex() const;

        virtual void performLayout(NVGcontext* ctx) override;
        virtual Vector2i preferredSize(NVGcontext* ctx) const override;
        virtual void addChild(int index, Widget* widget) override;

    private:
        int mSelectedIndex = -1;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

}