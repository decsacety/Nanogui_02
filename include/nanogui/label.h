#pragma once

#include<nanogui/widget.h>

namespace nanogui {

	class NANOGUI_EXPORT Label : public Widget {
	public:
		Label(Widget* parent, const std::string& caption, const std::string& font =
			"sans", int fontsize = -1);

		//in_class
		const std::string& caption() const { return mCaption; }
		void setCaption(const std::string& caption) { mCaption = caption; }
		void setFont(const std::string& font) { mFont = font; }
		const std::string& font() const { return mFont; }
		Color color()const { return mColor; }
		void setColor(const Color& color) { mColor = color; }

		int lsetMargin() { return leftMargin; }
		void setLeftMargin(int margin) { leftMargin = margin; }

		//virtual 
		virtual void setTheme(Theme* theme) override;
		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual void draw(NVGcontext* ctx) override;

	protected:
		std::string mCaption;
		std::string mFont;
		Color mColor;
		int leftMargin;
	public: EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

}