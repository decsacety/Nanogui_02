#pragma once
#include<nanogui/common.h>
#include<nanogui/object.h>

namespace nanogui {
	class NANOGUI_EXPORT Theme :public Object {
	public:
		Theme(NVGcontext* ctx);

		int mFontNormal;
		int mFontBold;
		int mFontIcons;
		float mIconScale;
		int mStandardFontSize;
		int mButtonFontSize;
		int mTextBoxFontSize;
		int mWindowCornerRadius;
		int mWindowHeaderHeight;
		int mWindowDropShadowSize;
		int mButtonCornerRadius;
		float mTabBorderWidth;		
		int mTabInnerMargin;
		int mTabMinButtonWidth;
		int mTabMaxButtonWidth;
		int mTabControlWidth;
		int mTabButtonHorizontalPadding;
		int mTabButtonVerticalPadding;

	};
}