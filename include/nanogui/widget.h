#pragma once 
#include<nanogui/common.h>
#include<nanogui/object.h>
#include<nanogui/theme.h>
#include<nanogui/layout.h>

#include<vector>

namespace nanogui {


	class NANOGUI_EXPORT Widget : public Object {
	public:
		Widget(Widget* parent);
		void addChild(Widget* widget);
		virtual void addChild(int index, Widget* widget);
		void removeChild(const Widget* widget);
		void removeChild(int index);
		const Widget* childAt(int index) const { return mChildren[index]; }
		Widget* childAt(int index) { return mChildren[index]; }
		Window* window();
		Screen* screen();

		int childCount() const { return (int)mChildren.size(); }
		void setParent(Widget* parent) { mParent = parent; }
		virtual void setTheme(Theme* theme);
		const Vector2i& position() const { return mPos; }
		const Vector2i& fixedSize() const { return mFixedSize; }
		int fixedWidth() const { return mFixedSize.x(); }
		int fixedHeight() const { return mFixedSize.y(); }

		const Theme* theme() const { return mTheme.get(); }
		int width() const { return mSize[0]; }
		int height()const { return mSize[1]; }
		void setPosition(const Vector2i& pos) { mPos = pos; }
		Vector2i absolutePosition() const {
			return mParent ? (parent()->absolutePosition() + mPos) : mPos;
		}
		const Vector2i& size() const { return mSize; }
		void requestFocus();
		void setLayout(Layout* layout) { mLayout = layout; }
		void setVisible(bool visible) { mVisible = visible; }
		bool visibleRecursive() const {
			bool visible = true;
			const Widget* widget = this;
			while (widget) {
				visible &= widget->visible();
				widget = widget->parent();
			}
			return visible;
		}
		
		void setSize(const Vector2i& size) { mSize = size; }
		void setFixedSize(const Vector2i& fixedSize) { mFixedSize = fixedSize; }
		void setFontSize(int fontSize) { mFontSize = fontSize; }
		void setFixedHeight(int height) { mFixedSize.y() = height; }

		bool visible() const { return mVisible; }
		void setEnabled(bool enable) { mEnabled = enable; }
		bool focused() const { return mFocused; }
		const std::vector<Widget*>& children() const { return mChildren; }
		const Widget* parent() const { return mParent; }
		Widget* parent() { return mParent; }
		Widget* findWidget(const Vector2i& p);
		Cursor cursor()const { return mCursor; }
		void setCursor(Cursor cursor) { mCursor = cursor; }
		int fontSize() const;
		bool contains(const Vector2i& p)const {
			auto d = (p - mPos).array();
			return (d >= 0).all() && (d < mSize.array()).all();
		}

		//子类需要实现/覆写的虚函数
		virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);
		virtual bool keyboardCharacterEvent(unsigned int codepoint);
		virtual Vector2i preferredSize(NVGcontext* ctx) const;
		virtual bool mouseDragEvent(const Vector2i&p, const Vector2i &rel, int button, int modifiers);
		virtual bool mouseMotionEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers);
		virtual bool mouseEnterEvent(const Vector2i& p, bool enter);
		virtual bool scrollEvent(const Vector2i& p, const Eigen::Vector2f& rel);
		virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers);
		virtual void performLayout(NVGcontext* ctx);
		virtual void draw(NVGcontext* ctx);
		virtual bool focusEvent(bool focused);
	
	protected:
		virtual ~Widget();
		inline float icon_scale() const { return mTheme->mIconScale * mIconExtraScale; }
	
	protected:
		Widget* mParent;
		ref<Theme> mTheme;
		ref<Layout> mLayout;
		std::string mId;
		Vector2i mPos, mSize, mFixedSize;
		std::vector<Widget*> mChildren;

		bool mVisible;

		bool mEnabled;
		bool mFocused, mMouseFocus;
		std::string mTooltip;
		int mFontSize;

		float mIconExtraScale;
		Cursor mCursor;

		Vector2i  MinSubWindowSize;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};


}
//回去看看 C#，C# 为啥会有 Object 这个类。C# 中的 Object 提供了哪些功能？