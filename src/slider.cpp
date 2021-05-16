/*
    nanogui/slider.cpp -- Fractional slider widget with mouse control
*/

#include<nanogui/slider.h>
#include<nanogui/theme.h>
#include<nanogui/screen.h>
#include<GLFW/glfw3.h>
#include<nanovg.h>

namespace nanogui {

    Slider::Slider(Widget* parent) :
        Widget(parent), mValue(0.0f), mRange(0.f, 1.f),
        mHighlightedRange(0.f, 0.f) {
        mHighlightColor = Color(255, 80, 80, 70);
        mActive = false;
    }

    Vector2i Slider::preferredSize(NVGcontext*) const {
        return Vector2i(100, 15);
    }

    bool Slider::mouseDragEvent(const Vector2i& p, const Vector2i&/*rel*/,
        int /*button*/, int /* modifiers*/) {
        if (!mEnabled)
            return false;

        const float kr = (int)(mSize.y() * .4f), kshadow = 3;
        const float startX = kr + kshadow + mPos.x() - 1;
        const float widthX = mSize.x() - 2 * (kr + kshadow);

        float value = (p.x() - startX) / widthX;
        value = value * (mRange.second - mRange.first) + mRange.first;
        mValue = std::min(std::max(value, mRange.first), mRange.second);
        if (mCallback)
            mCallback(mValue);
        return true;
    }

    bool Slider::mouseButtonEvent(const Vector2i& p, int /*button*/, bool down, int /*modifiers*/) {
        if (!mEnabled)
            return false;

        mActive = !mActive;

        const float kr = (int)(mSize.y() * .4f), kshadow = 3;
        const float startX = mPos.x();//kr + kshadow + mPos.x();
        const float widthX = mSize.x() - (kr + kshadow) + 2; //-2 * (kr + kshadow);
        /*const float starX = kr + kshadow + mPos.x() - 1;
        const float widthX = mSize.x() - 2 * (kr + kshadow);*/

        float value = (p.x() - startX) / widthX;
        value = value * (mRange.second - mRange.first) + mRange.first;
        mValue = std::min(std::max(value, mRange.first), mRange.second);
        if (mCallback)
            mCallback(mValue);
        if (mFinalCallback && !down)
            mFinalCallback(mValue);
        return true;
    }

    void Slider::draw(NVGcontext* ctx) {

        mSize.x() = (mParent->size().x()-mPos.x()) * .85f;
 

        Vector2f center = mPos.cast<float>() + mSize.cast<float>() * .5f;
        float kr = (int)(mSize.y() * .4f), kshadow = 3;

        float startX = mPos.x();//kr + kshadow + mPos.x();
        float widthX = mSize.x() - (kr + kshadow) + 2; //-2 * (kr + kshadow);

        Vector2f knobPos(startX + (mValue - mRange.first)/
        (mRange.second - mRange.first)* widthX,
            center.y() + .5f);

        NVGpaint bg;
        if(mActive&& mEnabled)
            bg = nvgBoxGradient(
                ctx, startX, center.y() - 3 + 1, widthX, 6, 3, 3,
                Color(0.26f, 0.59f, 0.98f, .80f), Color(0.26f, 0.59f, 0.98f, .8f)
            );
        else
            bg = nvgBoxGradient(
            ctx, startX, center.y() - 3 + 1, widthX, 6, 3, 3,
                mMouseFocus ? Color(0.26f, 0.59f, 0.98f, 0.4f): Color(0.26f, 0.59f, 0.98f, 0.30f), mMouseFocus ? Color(0.26f, 0.59f, 0.98f, 0.4f): Color(0.26f, 0.59f, 0.98f, 0.30f)
        );

        nvgBeginPath(ctx);
        //nvgRoundedRect(ctx, startX, center.y() - 3 + 1, widthX, 6, 2);
        nvgRestore(ctx);
        nvgSave(ctx);
        nvgIntersectScissor(ctx, mPos.x(), mPos.y(), mSize.x(), mSize.y());
        nvgRoundedRect(ctx, mPos.x(), mPos.y() , mSize.x(),
            mSize.y() , 0);
        nvgFillPaint(ctx, bg);
        nvgFill(ctx);

        if (mHighlightedRange.second != mHighlightedRange.first) {
            nvgBeginPath(ctx);
            nvgRoundedRect(ctx, startX + mHighlightedRange.first * mSize.x(),
                center.y() - kshadow + 1,
                widthX *
                (mHighlightedRange.second - mHighlightedRange.first),
                kshadow * 2, 2);
            nvgFillColor(ctx, mHighlightColor);
            nvgFill(ctx);
        }

        NVGpaint knobShadow =
            nvgRadialGradient(ctx, knobPos.x(), knobPos.y(), kr - kshadow,
                kr + kshadow, Color(0, 64), mTheme->mTransparent);

      /*  nvgBeginPath(ctx);
        nvgRect(ctx, knobPos.x() - kr - 5, knobPos.y() - kr - 5, kr * 2 + 10,
            kr * 2 + 10 + kshadow);
        nvgCircle(ctx, knobPos.x(), knobPos.y(), kr);
        nvgFillPaint(ctx, knobShadow);
        nvgFill(ctx);*/


        NVGpaint knob = nvgLinearGradient(ctx,
            mPos.x(), center.y() - kr, mPos.x(), center.y() + kr,
            mTheme->mButtonGradientBotFocused, mTheme->mButtonGradientBotFocused);
        NVGpaint knobReverse = nvgLinearGradient(ctx,
            mPos.x(), center.y() - kr, mPos.x(), center.y() + kr,
            mTheme->mButtonGradientBotFocused,
            mTheme->mButtonGradientBotFocused);

        nvgBeginPath(ctx);
        nvgRoundedRect(ctx, knobPos.x(), knobPos.y()-8, 7 ,
        15, 0);
        nvgStrokeColor(ctx, mTheme->mBorderDark);
        nvgFillPaint(ctx, knob);
        nvgFill(ctx);

        //Draw Text/ ±¾ÎÄ
        nvgFontSize(ctx, mTheme->mStandardFontSize);
        nvgFontFace(ctx, "sans-bold");
        nvgFillColor(ctx, mTheme->mTextColor);
        nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        std::string number = std::to_string(mValue);//knobPos.x() / mSize.x() * (mRange.second - mRange.first));
        number.resize(5);
        nvgText(ctx, center.x() - 12, mPos.y() + 3, number.c_str(), nullptr);

    }

}