#pragma once

#include<nanogui/window.h>

namespace nanogui {
	class NANOGUI_EXPORT Popup :public Window {
	public:
		enum Side{Left =0, Right};

		Popup(Widget* parent, Window* parentWindow);

		void setAnchorPos(const Vector2i& anchorPos) { mAnchorPos = anchorPos; }

		const Vector2i& anchorPos()const { return mAnchorPos; }

		void setAnchorHeight(int anchorHeight) { mAnchorHeight = anchorHeight; }
		int anchorHeight() const { return mAnchorHeight; }
		void setSide(Side popupSide) { mSide = popupSide; }
		Side side() const { return mSide; }
		Window* parentWindow() { return mParentWindow; }
		const Window* parentWindow()const { return mParentWindow; }
		
		virtual void performLayout(NVGcontext* ctx) override;
		virtual void draw(NVGcontext* ctx) override;

	protected:
		virtual void refreshRelativePlacement() override;

	protected:
		Window* mParentWindow;
		Vector2i mAnchorPos;
		int mAnchorHeight;
		Side mSide;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}