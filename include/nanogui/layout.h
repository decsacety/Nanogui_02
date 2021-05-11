#pragma once
#include<nanogui/object.h>
#include<nanogui/widget.h>
#include<cstdio>
#include<unordered_map>

namespace nanogui {

	enum class Alignment :uint8_t {
		Minimum =0,
		Middle,
		Maximum,
		Fill
	};

	/// The direction of data flow for a layout
	enum class Orientation {
		Horizontal =0, /// Layout expands on horizontal axis
		Vertical	///Layout expands on vertical axis
	};

	class NANOGUI_EXPORT Layout : public Object {
	public:
		virtual void performLayout(NVGcontext* ctx, Widget* widget) const = 0;
		virtual Vector2i preferredSize(NVGcontext *ctx, const Widget *widget) const = 0;
	protected:
		virtual ~Layout() {};
	};

	class NANOGUI_EXPORT GroupLayout : public Layout {
	public:
		/*
		* Create a GroupLayout
		* 
		* \param margin
		*	The Margin around th e widgets added
		* 
		* \param spacing 
		*	The spacing between widgets added
		* 
		* \param groupSpacing
		*	The spacing between groups (groups are defined by each Label added).
		* 
		* \param groupIndent
		*	The amount to indent widget in a group (underneath a Label)
		*/

		GroupLayout(int margin =15, int spacing =6, int groupSpacing = 14, 
			int groupIndent = 20)
			:mMargin(margin), mSpacing(spacing), mGroupSpacing(groupSpacing),
			mGroupIndent(groupIndent){}

		/// The margin of this GroupLayout
		int margin() const { return mMargin; }

		/// Sets the margin of this GFroupLayout
		void setMargin(int margin) { mMargin = margin; }

		/// The spacing between widgits of this GroupLayout
		int spacing() const { return mSpacing; }

		///Sets the spacing between widgets of this GroupLayout
		void setSpacing(int sp) { mSpacing = sp; }

		/// The indent of widgets in a group(underneath a Label) of this GroupLayout
		int groupIndent()const { return mGroupIndent; }

		///Sets the indent of widgets in a group (underneath a Label) of this GroupLayout
		void setGroupIndent(int gi) { mGroupIndent = gi; }

		///The spacing between groups of this GroupLayout
		int groupSpacing() const { return mGroupSpacing; }

		///Sets the spacing between of this GroupLayouty
		void setGroupSpacing(int gs) { mGroupSpacing = gs; }

		virtual Vector2i preferredSize(NVGcontext* ctx, const Widget* widget) const override;
		virtual void performLayout(NVGcontext* ctx, Widget* widget) const override;

	protected:
		int mMargin;
		int mSpacing;
		int mGroupSpacing;
		int mGroupIndent;

	};

	class NANOGUI_EXPORT AdvancedGridLayout : public Layout {
	public:
		struct Anchor {
			uint8_t pos[2];
			uint8_t size[2];
			Alignment align[2];

			Anchor(){}

			Anchor(int x, int y, Alignment horiz = Alignment::Fill,
				Alignment vert = Alignment::Fill) {
				pos[0] = (uint8_t)x; pos[1] = (uint8_t)y;
				size[0] = size[1] = 1;
				align[0] = horiz; align[1] = vert;
			}

			Anchor(int x, int y, int w, int h,
			Alignment horiz = Alignment::Fill
			, Alignment vert = Alignment::Fill) {
				pos[0] = (uint8_t)x; pos[1] = (uint8_t)y;
				size[0] = (uint8_t)w; size[1] = (uint8_t)h;
				align[0] = horiz; align[1] = vert;
			}

			operator std::string() const {
				char buf[50];
				std::snprintf(buf, 50, "Format[pos=(%i,%i), size=(%i,%i), align=(%i, %i)]"
				,pos[0], pos[1], size[0], size[1],(int)align[0], (int)align[1]);
				return buf;
			}
		};

		AdvancedGridLayout(const std::vector<int>& cols = {}
		, const std::vector<int>& rows = {}, int margin = 0);
		void computeLayout(NVGcontext* ctx, const Widget* widget,
			std::vector<int>* _grid) const;
		void setMargin(int margin) { mMargin = margin; }
		void setColStretch(int index, float stretch) { mColStretch.at(index) = stretch; }
		int rowCount() const { return (int)mRows.size(); }
		void appendRow(int size, float stretch = 0.f) { mRows.push_back(size); mRowStretch.push_back(stretch); }
		void setAnchor(const Widget* widget, const Anchor& anchor) { mAnchor[widget] = anchor; }
		
		Anchor anchor(const Widget* widget) const {
			auto it = mAnchor.find(widget);
			if (it == mAnchor.end())
				throw std::runtime_error("Widget was not registered with the grid layout");
			return it->second;
		}

		virtual Vector2i preferredSize(NVGcontext *ctx, const Widget *widget) const override;
		virtual void performLayout(NVGcontext* ctx, Widget* widget) const override;

	protected :
		std::vector<int> mCols;
		std::vector<int> mRows;
		std::vector<float> mColStretch;
		std::vector<float> mRowStretch;
		std::unordered_map<const Widget*, Anchor> mAnchor;
		int mMargin;
	};


}