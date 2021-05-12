/*
* 
* \brief Two-state check box Widget 
*/

#pragma once

#include<nanogui/widget.h>

namespace nanogui {

	/*
	* \remark
	*	This class overrides \ref nanogui::Widget::mIconExtraScale to be '1.2',
	*	which affects all subclasses of this Widget.  Subclasses must explicitly
	*	set a different value if needed(e. g , in their constructor).
	*/

	class NANOGUI_EXPORT CheckBox : public Widget {
	public:
		/*
		* Adds a ChackBox to the specified ''parent''
		*
		* \param parent
		*	The Widget to add this CheckBox to
		*
		* \param caption
		*	The caption text of the CheckBox(default ''Untitiled''
		*
		* \param callback
		*	if provided, the callback to execute when the CheckBox is checked or
		*	unchecked. Default parameter function does nothing. See
		*	\ref nanogui::CheckBox::mPushed for the difference between ''pushed''
		*	and ''checked''
		*
		*/
		CheckBox(Widget* parent, const std::string& caption = "Untitled",
			const std::function<void(bool)>& callback = std::function<void(bool)>());


		/// The caption of this checkBox
		const std::string& caption() const { return mCaption; }
		void setCaption(const std::string& caption) { mCaption = caption; }

		/// Whether or nor this CheckBox is currently checked
		const bool& checked() const { return mChecked; }
		void setChecked(const bool& che) { mChecked = che; }

		///WHether or not this CheckBox is currently pushed 
		const bool& pushed() const { return mPushed; }
		void setPushed(const bool& pushed) { mPushed = pushed; }

		///   Return the current callback of this CheckBox
		std::function<void(bool)> callback() const { return mCallback; }
		void setCallback(const std::function<void(bool)>& callback) { mCallback = callback; }

		///override the mouseButtonEvent callback
		virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down, int modifiers) override;

		///The preferred size of this CheckBox.
		virtual Vector2i preferredSize(NVGcontext* ctx) const override;

		/// Just for ∂‡Ã¨
		void setLabel(const std::string& label) {}

		/// Draws this CheckBox
		virtual void draw(NVGcontext* ctx) override;

	protected:
		/// The caption text of this CheckBox
		std::string mCaption;

		bool mPushed;

		bool mChecked;

		/// The funciton to execute when \ref nanogui::mCheckBox::mChecked is changed
		std::function<void(bool)> mCallback;

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};
}