#pragma once
#include<nanogui/screen.h>
#include<nanogui/window.h>
#include<nanogui/widget.h>
#include<nanogui/layout.h>
#include<nanogui/label.h>
#include<nanogui/button.h>
#include<nanogui/glutil.h>
#include<nanogui/textbox.h>
#include<nanogui/colorpicker.h>
#include<nanogui/checkbox.h>
#include<nanogui/combobox.h>

namespace nanogui {

	namespace detail {
		template <typename T, typename sfinae = std::true_type> class FormWidget {};
	}

	class FormHelper {
	public:  
		FormHelper(Screen* screen){
			mScreen = screen;
		}

		Window* addWindow(Vector2i pos , const char* title = "NoName")
		{
			mWindow = new Window(mScreen, title);
			mLayout = new AdvancedGridLayout({ 10,0,10,0 }, {});
			mLayout->setMargin(0);
			mLayout->setColStretch(2, 1);
			mWindow->setPosition(pos);
			mWindow->setLayout(mLayout);
			mWindow->setVisible(true);
			return mWindow;
		}

		Label* addText(const std::string& caption, int leftMargin = -1) {
			Label* label = new Label(mWindow, caption, mGroupFontName, mGroupFontSize);
			if (leftMargin != -1)
				label->setLeftMargin(leftMargin);
			if (mLayout->rowCount() > 0)
				mLayout->appendRow(mPreGroupSpacing);
			mLayout->appendRow(0);
			mLayout->setAnchor(label, AdvancedGridLayout::Anchor(0, mLayout->rowCount() - 1, 4, 1));
			mLayout->appendRow(mPostGroupSpacing);
			return label;
		}

		//Add a new data widget controlled using custom getter/setter functions
		template <typename Type> detail::FormWidget<Type>* 
			addVariable(const std::string& label, const std::function<void(const Type &)> &setter,
				const std::function<Type()>& getter, Type value,  bool editable = true) {
			//if (typeid(value) == typeid(Color)) {
			//}

			Label* labelW = new Label(mWindow, label, mLabelFontName, mLabelFontSize);
			labelW->setLeftMargin(mLeftMargin);//对于自动计算margin不尽人意的控件自行设定左边界距离
			auto widget = new detail::FormWidget<Type>(mWindow);
			auto refresh = [widget, getter] {
				Type value = getter(), current = widget->value();
				if (value != current)
					widget->setValue(value);
			};
			refresh();
			widget->setCallback(setter);
			widget->setEditable(editable);
			widget->setFontSize(mWidgetFontSize);
			widget->setLabel(label);
			Vector2i fs = widget->fixedSize();
			widget->setFixedSize(Vector2i(fs.x() != 0 ? fs.x() : mFixedSize.x(),
				fs.y() != 0 ? fs.y() : mFixedSize.y()));
			mRefreshCallbacks.push_back(refresh);
			if (mLayout->rowCount() > 0)
				mLayout->appendRow(mVariableSpacing);
			mLayout->appendRow(0);
			mLayout->setAnchor(labelW, AdvancedGridLayout::Anchor(1, mLayout->rowCount()-1));
			mLayout->setAnchor(widget, AdvancedGridLayout::Anchor(3, mLayout->rowCount() - 1));
			return widget;

		}

		template <typename Type> detail::FormWidget<Type> *
			addVariable(const std::string& label, Type &value, bool editable = true) {
			return addVariable<Type>(label,
				[&](const Type& v) {value = v; },
				[&]()->Type {return value; },
				value,
				editable
				);
		}

		Button* addButton(const std::string& label, const std::function<void()>& cb, std::string appendixText = "") {
			Button* button = new Button(mWindow, label,0, appendixText);
			button->setCallback(cb);
			button->setFixedHeight(15);//Button的高度
			if (mLayout->rowCount() > 0)
				mLayout->appendRow(mVariableSpacing);
			mLayout->appendRow(0);
			mLayout->setAnchor(button, AdvancedGridLayout::Anchor(1, mLayout->rowCount() - 1, 3, 1));
			mLayout->appendRow(mPostGroupSpacing);//增加一个PostSpacing作为与后面控件的间隔
			return button;
		}

	protected:
		ref<Screen> mScreen;
		ref<Window> mWindow;
		ref<AdvancedGridLayout> mLayout;

		std::vector<std::function<void()>> mRefreshCallbacks;

		std::string mGroupFontName = "sans-bold";
		std::string mLabelFontName = "sans";
		Vector2i mFixedSize = Vector2i(0, 20);
		int mGroupFontSize = 12;
		int mLabelFontSize = 14;
		int mWidgetFontSize = 12;
		int mPreGroupSpacing = 5;
		int mPostGroupSpacing = 5;
		int mVariableSpacing = 5;
		int mLeftMargin = 5;//左边界为5

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

	namespace detail {

		/*
		* A specialization for adding a CheckBox to a FormHelper.
		*/
		template <> class FormWidget<bool, std::true_type> : public CheckBox {
		public:
			/// Create a new FormWidget with underlying type CheckBox.
			FormWidget(Widget* p) : CheckBox(p, "") { setFixedWidth(20); }

			///Pass-throught function for \ref nanogui::CheckBox::setChecked
			void setValue(bool v) { setChecked(v); }

			/// Pass-through function for \ref nanogui::Widget::setEnabled 
			void setEditable(bool e) { setEnabled(e); }

			/// Returns the value of \ref nanogui::CheckBox::checked
			bool value() const { return checked(); }
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		/*
		* \tparam T
		*		The type being used inside the ComboBox
		*/
		template <typename T> class FormWidget<T, typename std::is_enum<T>::type> :public ComboBox {
		public:
			/// Creates a new FormWidget with underlying tyoe ComboBox.
			FormWidget(Widget* p) :ComboBox(p) {}

			/// Pass-through function for \ref nanogui::ComboBox::selectedIndex
			T value() const { return (T)selectedIndex(); }

			void setValue(T value) { setSelectedIndex((int)value); mSelectedIndex = (int)value; }

			/// Pass_through function for \red nanogui::ComboBox::setCallback
			void setCallback(const std::function<void(const T&)>& cb) {
				ComboBox::setCallback([cb](int v) {cb((T)v); });
			}

			/// Pass-through function for \ref nanogui::Widget::setEnabled
			void setEditable(bool e) {setEnabled(e);}

		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		template <typename T> class FormWidget<T, typename std::is_integral<T>::type> : public IntBox<T> {
		public:
			/// Create a new FormWidget with underlying type IntBox.
			FormWidget(Widget* p) : IntBox<T>(p) { this->setAlignment(TextBox::Alignment::Right); }
		
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		template <typename T> class FormWidget<T, typename std::is_floating_point<T>::type> : public FloatBox<T> {
		public:
			/// Create a new FormWidget with underlying type IntBox.
			FormWidget(Widget* p) : FloatBox<T>(p) { this->setAlignment(TextBox::Alignment::Right); }

		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		template <> class FormWidget<std::string, std::true_type> :public TextBox {
		public:
			FormWidget(Widget* p) :TextBox(p) { setAlignment(TextBox::Alignment::Left); }

			///Pass-through function for \ref nanogui::TextBox::setCallback.
			void setCallback(const std::function<void(const std::string&)>& cb) {
				TextBox::setCallback([cb](const std::string& str) { cb(str); return true; });
			}
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW
		};

		template<> class FormWidget<Color, std::true_type> :public ColorPicker {
		public:
			///Create a new FormWidget with underlying type ColorPicker
			FormWidget(Widget* p) :ColorPicker(p){}

			void setValue(const Color& c) { setColor(c); }

			void setEditable(bool e) { setEnabled(e); }

			Color value() const { return color(); }

		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW

			///
		};

	}

}