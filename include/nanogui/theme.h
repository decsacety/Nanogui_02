#pragma once
#include<nanogui/common.h>
#include<nanogui/object.h>

namespace nanogui {
	class NANOGUI_EXPORT Theme :public Object {
	public:
		Theme(NVGcontext* ctx);

		//fonts
		int mFontNormal;
		int mFontBold;
		int mFontIcons;

		float mIconScale;

		//Spacing-related paramters
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
		Color mButtonGradientTopFocused;
		Color mButtonGradientBotFocused;
		Color mButtonGradientTopUnfocused;
		Color mButtonGradientBotUnfocused;
		Color mButtonGradientTopPushed;
		Color mButtonGradientBotPushed;

		//Window colors
		Color mWindowFillUnfocused;
		Color mWindowFillFocused;
		Color mWindowTitleUnfocused;
		Color mWindowTitleFocused;
		//WIndows headings
		Color mWindowUnfHeaderGradientTop;
		Color mWindowUnfHeaderGradientBot;
		Color mWindowHeaderGradientTop;
		Color mWindowHeaderGradientBot;
		Color mWindowHeaderSepTop;
		Color mWindowHeaderSepBot;

		//The Popup window color 
		Color mWindowPopup;

		//The transparent Window color
		Color mWindowPopupTransparent;

		///Icon to use for CheckBox widget (default: ENTYPO_ICON_CHRCK)
		int mCheckBoxIcon;
		int mMessageInformationIcon;
		int mMessageQuestionIcon;
		int mMessageWarningIcon;
		int mMessageAltButtonIcon;
		int mMessagePrimaryButtonIcon;
		int mPopupChevronRightIcon;
		int mPopupChevronLeftIcon;
		int mTabHeaderLeftIcon;
		int mTabHeaderRightIcon;
		int mTextBoxUpIcon;
		int mTextBoxDownIcon;

	protected:
		virtual ~Theme() {};

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};
}