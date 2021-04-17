#include<nanogui/theme.h>

namespace nanogui {
	Theme::Theme(NVGcontext* ctx) {
        mStandardFontSize = 16;
        mButtonFontSize = 20;
        mTextBoxFontSize = 20;
        mIconScale = 0.77f;

        mWindowCornerRadius = 2;
        mWindowHeaderHeight = 30;
        mWindowDropShadowSize = 10;
        mButtonCornerRadius = 2;
        mTabBorderWidth = 0.75f;
        mTabInnerMargin = 5;
        mTabMinButtonWidth = 20;
        mTabMaxButtonWidth = 160;
        mTabControlWidth = 20;
        mTabButtonHorizontalPadding = 10;
        mTabButtonVerticalPadding = 2;


	}
}