#pragma once
#pragma warning(disable : 4091)//可控的c4091警告
#include<nanogui/widget.h>
#include<iostream>

namespace nanogui {
	NANOGUI_EXPORT class Window :public Widget{
		friend class Popup;
	public:
		NANOGUI_EXPORT Window(Widget* parent, const char* title = "Untitle");
		const std::string& title() const { return mTitle; }
		void setTitle(const std::string& title) { mTitle = title; }

		bool modal() const { return mModal; }
		void setModal(bool modal) { mModal = modal; }

		Widget* buttonPanel();

		void dispose();

		void center();
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
		//const char* mTitle;
		std::string mTitle;
		Widget* mButtonPanel;
		bool mModal;
		bool mDrag;
		int pre_mSize_y;//Y轴历史大小
		bool isFold;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}