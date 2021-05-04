#include<nanogui/theme.h>
#include<font/nanogui_resources.h>
#include<nanovg.h>

namespace nanogui {
	Theme::Theme(NVGcontext* ctx) {
        mStandardFontSize                       = 16;
        mButtonFontSize                         = 20;
        mTextBoxFontSize                        = 20;
        mIconScale                              = 0.77f;

        mWindowCornerRadius                     = 2;
        mWindowHeaderHeight                     = 20;
        mWindowDropShadowSize                   = 5;//ԭΪ10
        mButtonCornerRadius                     = 2;
        mTabBorderWidth                         = 0.75f;
        mTabInnerMargin                         = 5;
        mTabMinButtonWidth                      = 20;
        mTabMaxButtonWidth                      = 160;
        mTabControlWidth                        = 20;
        mTabButtonHorizontalPadding             = 10;
        mTabButtonVerticalPadding               = 2;

        mDropShadow                             = Color(0, 68);
        mTransparent                            = Color(0, 0);
        mBorderDark                             = Color(29, 255);
        mBorderLight                            = Color(92, 255);
        mBorderMedium                           = Color(35, 255);
        mTextColor                              = Color(255, 250);
        mDisabledTextColor                      = Color(255, 80);
        mTextColorShadow                        = Color(0, 160);
        mIconColor                              = mTextColor;

        //WIndow_related
        mWindowFillUnfocused                    = Color(13, 230);
        mWindowFillFocused                      = Color(15, 230);
        mWindowTitleUnfocused                   = Color(255, 240);
        mWindowTitleFocused                     = Color(255, 240);

        //Window header
        mWindowHeaderGradientTop                = Color(10, 255);
        mWindowHeaderGradientBot                = Color(10, 255);
        mWindowUnfHeaderGradientTop             = Color(0.1843f, 0.29f, 0.47843f, 0.99f);
        mWindowUnfHeaderGradientBot             = Color(0.1843f, 0.29f, 0.47843f, 0.99f);
        mWindowHeaderSepTop                     = Color(41, 255);
        mWindowHeaderSepBot                     = Color(29, 255);

        mFontNormal = nvgCreateFontMem(ctx, "sans", roboto_regular_ttf,
            roboto_regular_ttf_size, 0);
        mFontBold = nvgCreateFontMem(ctx, "sans-bold", roboto_bold_ttf,
            roboto_bold_ttf_size, 0);
        mFontIcons = nvgCreateFontMem(ctx, "icons", entypo_ttf,
            entypo_ttf_size, 0);
        if (mFontNormal == -1 || mFontBold == -1 || mFontIcons == -1)
            throw std::runtime_error("Could not load fonts");
	}
}