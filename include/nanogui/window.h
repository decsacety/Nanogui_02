#pragma once
#include<nanogui/common.h>
#include<nanogui/widget.h>
#include<iostream>

namespace nanogui {
	NANOGUI_EXPORT class Window :public Widget{
	public:
		NANOGUI_EXPORT Window(Widget* parent, const char* title = "Untitle");
		const std::string title() const { std::string l = mTitle; return l; }

		bool modal() const { return mModal; }
		void setModal(bool modal) { mModal = modal; }

		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual void performLayout(NVGcontext* ctx) override;
		virtual void draw(NVGcontext* ctx) override;
		virtual void refreshRelativePlacement();
	protected :
	protected:
		const char* mTitle;
		Widget* mButtonPanel;
		bool mModal;
		bool mDrag; 
	public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}