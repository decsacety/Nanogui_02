#include<nanogui/layout.h>
#include<nanogui/window.h>
#include<numeric>

namespace nanogui {
	AdvancedGridLayout::AdvancedGridLayout(const std::vector<int>& cols
		, const std::vector<int>& rows , int margin ) 
		: mCols(cols), mRows(rows),mMargin(margin)
	{
		mColStretch.resize(mCols.size(), 0);
		mRowStretch.resize(mRows.size(), 0);
	}
	void AdvancedGridLayout::performLayout(NVGcontext* ctx, Widget* widget) const {
		std::vector<int> grid[2];
		computeLayout(ctx, widget, grid);

		grid[0].insert(grid[0].begin(), mMargin);
		const Window* window = dynamic_cast<const Window*>(widget);
		if (window && !window->title().empty())
			grid[1].insert(grid[1].begin(), widget->theme()->mWindowHeaderHeight + mMargin / 2);
		else
			grid[1].insert(grid[1].begin(), mMargin);

		for (int axis = 0; axis < 2; ++axis) {
			for (size_t i = 1; i < grid[axis].size(); ++i)
				grid[axis][i] += grid[axis][i - 1];
		}

	}

	void AdvancedGridLayout::computeLayout(NVGcontext* ctx,const Widget* widget,
		std::vector<int>* _grid) const {
		Vector2i fs_w = widget->fixedSize();
		Vector2i containerSize(
			fs_w[0] ? fs_w[0] : widget->width(),
			fs_w[1] ? fs_w[1] : widget->height()
		);

		Vector2i extra = Vector2i::Constant(2 * mMargin);
		const Window* window = dynamic_cast<const Window*> (widget);
		if (window && !window->title().empty())
			extra[1] += widget->theme()->mWindowHeaderHeight - mMargin / 2;

		containerSize -= extra;

	}

	Vector2i AdvancedGridLayout::preferredSize(NVGcontext* ctx, const Widget* widget) const {
		std::vector<int>grid[2];
		computeLayout(ctx, widget, grid);

		Vector2i size(
			std::accumulate(grid[0].begin(), grid[0].end(), 0),
			std::accumulate(grid[1].begin(), grid[1].end(), 0)
		);

		Vector2i extra = Vector2i::Constant(2 * mMargin);
		const Window* window = dynamic_cast<const Window*>(widget);
		if (window && !window->title().empty())
			extra[1] += widget->theme()->mWindowHeaderHeight - mMargin / 2;

		return size + extra;
	}
}