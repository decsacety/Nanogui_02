#include<nanogui/layout.h>
#include<nanogui/window.h>
#include<nanogui/label.h>
#include<numeric>

namespace nanogui {

	Vector2i GroupLayout::preferredSize(NVGcontext* ctx,const Widget* widget) const {
		
		int height = mMargin, width = 2 * mMargin;

		const Window* window = dynamic_cast<const Window*>(widget);
		if (window && !window->title().empty())
			height += widget->theme()->mWindowHeaderHeight - mMargin / 2;

		bool first = true, indent = false;
		for (auto c : widget->children()) {
			if (!c->visible())
				continue;
			const Label* label = dynamic_cast<const Label*>(c);
			if (!first)
				height += (label == nullptr) ? mSpacing : mGroupSpacing;
			first = false;

			Vector2i ps = c->preferredSize(ctx), fs = c->fixedSize();
			Vector2i targetSize(
				fs[0] ? fs[0] : ps[0],
				fs[1] ? fs[1] : ps[1]
			);

			bool indentCur = indent && label == nullptr;
			height += targetSize.y();
			width = std::max(width, targetSize.x() + 2 * mMargin + (indentCur ? mGroupIndent : 0));

			if (label)
				indent = !label->caption().empty();
		}
		height += mMargin;
		return Vector2i(width, height);

	}

	void GroupLayout::performLayout(NVGcontext* ctx, Widget* widget) const {
		int height = mMargin, availabelWidth =
			(widget->fixedWidth() ? widget->fixedWidth() : widget->width()) - 2 * mMargin;

		const Window* window = dynamic_cast<const Window*>(widget);
		if (window && !window->title().empty())
			height += widget->theme()->mWindowHeaderHeight-mMargin/2;

		bool first = true, indent = false;
		for (auto c : widget->children()) {
			if (!c->visible())
				continue;
			const Label* label = dynamic_cast<const Label*>(c);
			if (!first)
				height += (label == nullptr) ? mSpacing : mGroupSpacing;
			first = false;

			bool indentCur = indent && label == nullptr;
			Vector2i ps = Vector2i(availabelWidth - (indentCur ? mGroupIndent : 0),
				c->preferredSize(ctx).y());
			Vector2i fs = c->fixedSize();

			Vector2i targetSize(
				fs[0] ? fs[0] : ps[0],
				fs[1] ? fs[1] : ps[1]
			);

			c->setPosition(Vector2i(mMargin + (indentCur ? mGroupIndent : 0), height));
			c->setSize(targetSize);
			c->performLayout(ctx);

			height += targetSize.y();

			if (label)
				indent = !label->caption().empty();
		}
	}


	AdvancedGridLayout::AdvancedGridLayout(const std::vector<int>& cols
		, const std::vector<int>& rows , int margin ) 
		: mCols(cols), mRows(rows),mMargin(margin)
	{
		mColStretch.resize(mCols.size(), 0);
		mRowStretch.resize(mRows.size(), 0);
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

		extra[0] += 10;//增加10像素作为右边框
		extra[1] += 15;//增加15像素作为下边框

		return size + extra;
	}

	void AdvancedGridLayout::performLayout(NVGcontext* ctx, Widget* widget) const {
		std::vector<int> grid[2];
		computeLayout(ctx, widget, grid);

		grid[0].insert(grid[0].begin(), mMargin+5);//增加五像素作为左边框
		const Window* window = dynamic_cast<const Window*>(widget);
		if (window && !window->title().empty())
			grid[1].insert(grid[1].begin(), widget->theme()->mWindowHeaderHeight + (10+mMargin / 2));//增加10像素作为第一个Text的上边框
		else
			grid[1].insert(grid[1].begin(), mMargin+5);

		for (int axis = 0; axis < 2; ++axis) {
			for (size_t i = 1; i < grid[axis].size(); ++i)
				grid[axis][i] += grid[axis][i - 1];

			for (Widget* w: widget->children()) {
				if (!w->visible())
					continue;
				Anchor anchor = this->anchor(w);

				int itemPos = grid[axis][anchor.pos[axis]];
				int cellSize = grid[axis][anchor.pos[axis] + anchor.size[axis]] - itemPos;
				int ps = w->preferredSize(ctx)[axis], fs = w->fixedSize()[axis];
				int targetSize = fs ? fs : ps;

				switch (anchor.align[axis]) {
				case Alignment::Minimum:
					break;
				case Alignment::Middle:
					itemPos += (cellSize - targetSize) / 2;
					break;
				case Alignment::Maximum:
					itemPos += cellSize - targetSize;
				case Alignment::Fill:
					targetSize = fs ? fs : cellSize;
					break;
				}

				Vector2i pos = w->position(), size = w->size();
				pos[axis] = itemPos;
				size[axis] = targetSize;
				w->setPosition(pos);
				w->setSize(size);
				w->performLayout(ctx);

			}

		}

	}


	void AdvancedGridLayout::computeLayout(NVGcontext* ctx, const Widget* widget,
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

		for (int axis = 0; axis < 2; ++axis) {
			std::vector<int>& grid = _grid[axis];
			const std::vector<int>& sizes = axis == 0 ? mCols : mRows;
			const std::vector<float>& stretch = axis == 0 ? mColStretch : mRowStretch;
			grid = sizes;

			for (int phase = 0; phase < 2; ++phase) {
				for (auto pair : mAnchor) {
					const Widget* w = pair.first;
					if (!w->visible())
						continue;
					const Anchor& anchor = pair.second;
					if ((anchor.size[axis] == 1) != (phase == 0))
						continue;
					int ps = w->preferredSize(ctx)[axis], fs = w->fixedSize()[axis];
					int targetSize = fs ? fs : ps;

					if (anchor.pos[axis] + anchor.size[axis] > (int)grid.size())
						throw std::runtime_error(
							"Advanced grid layout: widget is out of bounds: " +
							(std::string)anchor);

					int currentSize = 0;
					float totalStretch = 0;
					for (int i = anchor.pos[axis];
						i < anchor.pos[axis] + anchor.size[axis]; ++i) {
						if (sizes[i] == 0 && anchor.size[axis] == 1)
							grid[i] = std::max(grid[i], targetSize);
						currentSize += grid[i];
						totalStretch += stretch[i];
					}
					if (targetSize <= currentSize)
						continue;
					if (totalStretch == 0)
						throw std::runtime_error(
							"Advanced grid layout: no space to place widget: " +
							(std::string)anchor);
					float amt = (targetSize - currentSize) / totalStretch;
					for (int i = anchor.pos[axis];
						i < anchor.pos[axis] + anchor.size[axis]; ++i) {
						grid[i] += (int)std::round(amt * stretch[i]);
					}

				}
			}

			int currentSize = std::accumulate(grid.begin(), grid.end(), 0);
			float totalStretch = std::accumulate(stretch.begin(), stretch.end(), 0.0f);
			if (currentSize >= containerSize[axis] || totalStretch == 0)
				continue;
			float amt = (containerSize[axis] - currentSize) / totalStretch;
			for (size_t i = 0; i < grid.size(); ++i)
				grid[i] += (int)std::round(amt * stretch[i]);
		}

	}

}