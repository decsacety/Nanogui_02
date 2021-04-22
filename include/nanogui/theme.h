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

		//Generic colors
		Color mDropShadow;
		Color mTransparent;
		Color mBorderDark;
		Color mBorderLight;
		Color mBorderMedium;
		Color mTextColor;
		Color mDisabledTextColor;
		Color mTextColorShadow;
		Color mIconColor;

		//Button colors;

		//Window colors
		Color mWindowFillUnfocused;
		Color mWindowFillFocused;
		Color mWindowTitleUnfocused;
		Color mWindowTitleFocused;
		//WIndows headings
		Color mWindowHeaderGradientTop;
		Color mWindowHeaderGradientBot;
		Color mWindowHeaderSepTop;
		Color mWindowHeaderSepBot;

		//The Popup window color 
		Color mWindowPopup;

		//The transparent Window color
		Color mWindowPopupTransparent;



	};
}