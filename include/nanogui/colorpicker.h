/*
* \file nanogui/colorpicker.h
* 
* \brief Push button with a popup to tweak a color value. This Widget was 
* contributed by me
*/

#pragma once

#include<nanogui/popupbutton.h>
#include<nanogui/colorwheel.h>

namespace nanogui {

	/*
	* \class ColorPicker colorpicker.h nanogui/coloerpicker.h
	* 
	* \brief Push button with a popup to tweak a color value. 
	*/

	class NANOGUI_EXPORT ColorPicker :public PopupButton {
	public:
		/*
		* Attaches a ColorPicker to the specified parent
		* 
		* \param parent
		*	The Widget to add this ColorPicker to.
		* 
		* \param color
		*	The color initially selected by this ColorPicker (Default: Red)
		* 
		*/
		ColorPicker(Widget* parent, const Color& color = Color(1.0f, 0.f, 0.f, 1.f));

		///The callback executed when the ColorWheel changes/
		std::function<void(const Color&)> callback() const { return  mCallback; }

		/*
		* Sets the callback is executed as the ColorWheel itself is changed.  Set
		* This callback if you need to receive updates for the ColorWheel changing
		* before the user clicks \ref nanogui::ColorPicker::mPickButton or 
		* \ref nanogui::ColorPicker::mPickButton
		*/
		void setCallback(const std::function<void(const Color&)> callback) {
			mCallback = callback;
		}

		/*
		* The callback to execute when a new Color is selected on the ColorWheel
		* "and" the user clicks the \ref nanogui::ColorPicker::mPickButton or 
		* \ref nanogui::ColorPicker::mResetButton
		*/
		std::function<void(const Color&)> finalCallback() const { return mFinalCallback; }

		/*
		* The callback to execute when a new Color is selected on the Colorwheel
		* ""and"" the user clicks the \ref nanogui::ColorPicker::mPickButton or
		* \ref nanogui::colorPicker::mResetButton
		*/
		void setFinalCallback(const std::function<void(const Color&)>& callback) {
			mFinalCallback = callback;
		}
		
		// Get the current Color selected for this ColorPicker
		Color color() const;

		/// set the current the Color selected for this ColorPicker
		void setColor(const Color& color);

		/// The current caption of the \ref nanogui::ColorPicker::mPickButton
		const std::string& pickButtonCaption() { return mPickButton->caption(); }

		///sets the current caption of the \ref nanogui::Colorpicker;:mPickButotn
		void setPickButtonCaption(const std::string caption) {
			mPickButton -> setCaption(caption);
		}

		std::string& Label() { return mLabel; }
		void setLabel(const std::string& label) { mLabel = label; }

		///The current caption of the \ref nanogui::ColorPicker::mResetButton
		const std::string& resetButtonCaption() { return mResetButton->caption(); }

		///Set the current caption of the \ref nanogui::ColorPicker::mResetButton
		void setResetButtonCaption(const std::string& caption) {
			mResetButton->setCaption(caption);
		}


	protected:
		/// The "fast" callback executed when the ColorWheel has changed.
		std::function<void(const Color&)> mCallback;

		/*
		* The callback to executed when a new Color is selected on the ColorWheel
		* **and** the user clicks the \ref nanogui::ColorPicker::mPickButton or 
		* \rel nanogui::ColorPicker::mResetButton
		*/
		std::function<void(const Color&)> mFinalCallback;

		ColorWheel* mColorWheel;

		/*
		* The Button used to signal that the current value on the ColorWheel is the desired color
		* to be chosen.  The default value for the caption of this 
		* Button is "pick", You can change it using
		* \ref nanogui::ColorPicker::setPickButtonCaption if you need
		* 
		* The color of this Button will not affect \ref nanogui::ColorPicker::color
		* until the user has actively selected by clicking this pick button.
		* Similarly, the \ref nanogui::ColorPicker::mCallback function is only
		* called when a user selects a new Color using by clicking this button
		*/
		Button* mPickButton;

		/*
		* Remains the Color of the active color selection, until the user picks a 
		* new Color on the ColorWheel *and* selects the 
		* \rel nanogui::ColorPicker::mPickerButton. The default value for the 
		* caption of this Button is "reset" You can change it using
		* \ref nanogui::ColorPicker::setResetButtonCaption if you need
		*/
		Button* mResetButton;

		std::string mLabel;

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

}