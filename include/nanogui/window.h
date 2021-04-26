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

		//void setSize(int x, int y) { mSize.x() = x; mSize.y() = y; }

		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual void performLayout(NVGcontext* ctx) override;
		virtual void draw(NVGcontext* ctx) override;
		virtual void refreshRelativePlacement();
		virtual bool mouseDragEvent(const Vector2i& p, const Vector2i& rel,
			int button, int modifiers) override;
		virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down
			, int modifiers) override;
	protected:

	protected:
		const char* mTitle;
		Widget* mButtonPanel;
		bool mModal;
		bool mDrag; 
	public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}