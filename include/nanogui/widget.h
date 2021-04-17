#pragma once 
#include<nanogui/common.h>
#include<nanogui/object.h>
#include<nanogui/theme.h>
#include<nanogui/layout.h>

#include<vector>

namespace nanogui {

	enum class Cursor;

	class NANOGUI_EXPORT Widget : public Object {
	public:
		Widget(Widget* parent);
		void addChild(Widget* widget);
		void addChild(int index, Widget* widget);
		int childCount() const { return (int)mChildren.size(); }
		void setParent(Widget* parent) { mParent = parent; }
		virtual void setTheme(Theme* theme);
		const Vector2i& fixedSize() const { return mFixedSize; }
		const Theme* theme() const { return mTheme.get(); }
		int width() const { return mSize[0]; }
		int height()const { return mSize[1]; }
		void setPosition(const Vector2i& pos) { mPos = pos; }
		void setLayout(Layout* layout) { mLayout = layout; }
		void setVisible(bool visible) { mVisible = visible; }
		virtual Vector2i preferredSize(NVGcontext* ctx) const;
		virtual void performLayout(NVGcontext* ctx);
		void setSize(const Vector2i& size) { mSize = size; }
	protected:
		ref<Theme> mTheme;
		ref<Layout> mLayout;
		Widget* mParent;
		std::vector<Widget*> mChildren;
		Vector2i mPos, mSize, mFixedSize;
		bool mVisible;
	};


}
//回去看看 C#，C# 为啥会有 Object 这个类。C# 中的 Object 提供了哪些功能？