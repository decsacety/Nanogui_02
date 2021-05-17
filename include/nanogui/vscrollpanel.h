/*
    nanogui/vscrollpanel.h -- Adds a vertical scrollbar around a widget
    that is too big to fit into a certain area
*/


#pragma once 

#include<nanogui/widget.h>

namespace nanogui {

    class NANOGUI_EXPORT VScrollPanel :public Widget {

    public:
        VScrollPanel(Widget* parent);

        /// Return the current scroll amount as a value between 0 and 1.o0 means scrolled
        // to the top and 1 to the bottom.
        float scroll() const { return mScroll; }

        // Set the scroll amount to a value between 0 and 1.0 means scrolled to the 
        //top and 1 to the bottom
        void setScroll(float scroll) { mScroll = scroll; }

        virtual void performLayout(NVGcontext* ctx) override;
        virtual Vector2i preferredSize(NVGcontext* ctx)const override;
        virtual bool mouseDragEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;
        virtual bool scrollEvent(const Vector2i& p, const Vector2f& rel) override;
        virtual void draw(NVGcontext* ctx) override;

    protected:
        int mChildPreferredHeight;
        float mScroll;
        bool mUpdateLayout;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW


    };

}