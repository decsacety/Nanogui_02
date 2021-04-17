#pragma once
#include<nanogui/object.h>
#include<nanogui/widget.h>
#include<cstdio>
#include<unordered_map>

namespace nanogui {
	class NANOGUI_EXPORT Layout : public Object {
	public:
		virtual void performLayout(NVGcontext* ctx, Widget* widget) const = 0;
		virtual Vector2i preferredSize(NVGcontext *ctx, const Widget *widget) const = 0;
	protected:
		virtual ~Layout() {};
	};

	class NANOGUI_EXPORT AdvancedGridLayout : public Layout {
	public:
		AdvancedGridLayout(const std::vector<int>& cols = {}
		, const std::vector<int>& rows = {}, int margin = 0);
		void computeLayout(NVGcontext* ctx, const Widget* widget,
			std::vector<int>* _grid) const;
		void setMargin(int margin) { mMargin = margin; }
		void setColStretch(int index, float stretch) { mColStretch.at(index) = stretch; }
		virtual void performLayout(NVGcontext* ctx, Widget* widget) const override;
		virtual Vector2i preferredSize(NVGcontext *ctx, const Widget *widget) const override;

	protected :
		std::vector<int> mCols;
		std::vector<int> mRows;
		std::vector<float> mColStretch;
		std::vector<float> mRowStretch;
		int mMargin;
	};


}