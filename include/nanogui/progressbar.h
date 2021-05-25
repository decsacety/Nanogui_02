/*
    nanogui/progressbar.h -- Standard widget for visualizing progress
*/

#pragma once 

#include<nanogui/widget.h>

namespace nanogui {

    class NANOGUI_EXPORT ProgressBar :public Widget {
    public:
        ProgressBar(Widget* parent);

        float value() { return mValue; }
        void setValue(float value) { mValue = value; }

        virtual Vector2i preferredSize(NVGcontext* ctx)const override;
        virtual void draw(NVGcontext* ctx) override;

    protected:
        float mValue;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

}