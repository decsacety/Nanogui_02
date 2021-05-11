#pragma once 
#include<nanogui/widget.h>

namespace nanogui {
	class NANOGUI_EXPORT Button :public Widget {
	public:
		enum Flags {
			NormalButton = (1<<0),
			RadioButton = (1<<1),
			ToggleButton = (1<<2),
			PopupButton = (1<<3)
		};
		enum class IconPosition {
			Left,
			LeftCentered,
			RightCentered,
			Right
		};

		Button(Widget* parent, const std::string& caption = "Untitled HuaQ!"
			, int icon = 0, const std::string& appendixText = "");
		
		//对于每个protected值的set和get方法
		const std::string& caption() const { return mCaption; }
		void setCaption(const std::string & caption) { mCaption = caption; }
		
		const Color& backgroundColor() const { return mBackgroundColor; }
		void setBackgroundColor(const Color& backgroundColor) { mBackgroundColor = backgroundColor; }
		
		const Color& textColor() const { return mTextColor; }
		void setTextColor(const Color& textColor) { mTextColor = textColor; }

		const std::string& appendixText() { return mAppendixText; }
		void setAppendixText(const std::string& appendix) { mAppendixText = appendix; }
		
		int icon() const { return mIcon; }
		void setIcon(int icon) { mIcon = icon; }
		
		int flags() const { return mFlags; }
		void setFlags(int buttonFlags) { mFlags = buttonFlags; }
		
		IconPosition iconPostion() const { return mIconPosition; }
		void setIconPosition(IconPosition iconPosition) { mIconPosition = iconPosition; }
		
		bool pushed() const { return mPushed; }
		void setPushed(bool pushed) { mPushed = pushed; }
		
		std::function<void()> callback() const { return mCallback; }
		void setCallback(const std::function<void()>& callback) { mCallback = callback; }
		
		std::function<void(bool)> changeCallback() const { return mChangeCallback; }
		void setChangeCallback(const std::function<void(bool)>& changeCallback) { mChangeCallback = changeCallback; }
		
		const std::vector<Button* >& buttonGroup() const { return mButtonGroup; }
		void setButtonGroup(const std::vector<Button*>& buttonGroup) { mButtonGroup = buttonGroup; }

		//虚函数
		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) override;
		virtual void draw(NVGcontext* ctx) override;
	protected:
		std::string mCaption;

		std::string mAppendixText;//和button在同一行的文本
		int mIcon;
		IconPosition mIconPosition;
		bool mPushed;
		int mFlags;
		Color mBackgroundColor;
		Color mTextColor;
		std::function<void()> mCallback;
		std::function<void(bool)> mChangeCallback;//记得再添加一个参数为count的callback;
		std::vector <Button*> mButtonGroup;


	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

}