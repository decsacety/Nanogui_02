/*
* nanogui/popupbutton.h --Button which launches a popup widget
*/

#pragma once 

#include<nanogui/button.h>
#include<nanogui/popup.h>
#include<nanogui/entypo.h>

namespace nanogui {

	class NANOGUI_EXPORT PopupButton : public Button {
	public:
		PopupButton(Widget* parent, const std::string& caption = "Untitled",
			int buttonIcon = 0);
		virtual ~PopupButton();

		void setChevronIcon(int icon) { mChevronIcon = icon; }
		int chevronIcon() const { return mChevronIcon; }

		void setSide(Popup::Side popupSide);
		Popup::Side side() const { return mPopup->side(); }

		Popup* popup() { return mPopup; }
		const Popup* popup() const { return mPopup; }

		virtual void draw(NVGcontext* ctx) override;
		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual void performLayout(NVGcontext* ctx) override;

	protected:
		Popup* mPopup;
		int mChevronIcon;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};


}