/*
    nanogui/slider.h -- Fractional slider widget with mouse control
*/

#pragma once

#include<nanogui/widget.h>

namespace nanogui {

    /*
    * \class Slider slider.h nanogui/slider.h
    * 
    * \brief Factional slider widget with mouse control
    */

    class NANOGUI_EXPORT Slider :public Widget {
    public:
        Slider(Widget* parent);

        float value() const { return mValue; }
        void setValue(float value) { mValue = value; }

        const Color& highlightColor() const { return mHighlightColor; }
        void setHighlightColor(const Color& highlightColor) { mHighlightColor = highlightColor; }

        std::pair<float, float> range() const { return mRange; }
        void setRange(std::pair<float, float> range) { mRange = range; }

        std::function<void(float)> callback() const { return mCallback; }
        void setCallback(const std::function<void(float)>& callback) { mCallback = callback; }

        std::function<void(float)> finalCallback() const { return mFinalCallback; }
        void setFinalCallback(const std::function<void(float)> finalcb) { mFinalCallback = finalcb; }

        virtual Vector2i preferredSize(NVGcontext * ctx) const override;
        virtual bool mouseDragEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;
        virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) override;
        virtual void draw(NVGcontext* ctx) override;

    protected:
        float mValue;
        std::function<void(float)> mCallback;
        std::function<void(float)> mFinalCallback;
        std::pair<float, float>mRange;
        std::pair<float, float> mHighlightedRange;
        Color mHighlightColor;
        bool mActive;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

}