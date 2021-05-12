/*
* \brief Simple combo box widget based on a popup button
* 
*/

#pragma once

#include <nanogui/popupbutton.h>

namespace nanogui {

	/*
	* \brief Simple combo box widget based on a popup button
	*
	*/
	class NANOGUI_EXPORT ComboBox :public PopupButton {
	public:
		///Create an empty combo box
		ComboBox(Widget* parent);

		///Create a new combo box with the given items
		ComboBox(Widget* parent, const std::vector<std::string>& items);

		/*
		* \brief Create a bew combo box with the given items, providing both short
		* and long descriptive labels for each item
		*/
		ComboBox(Widget* parent, const std::vector<std::string>& items,
			const std::vector<std::string>& itemsShort);

		///The callback to execute for this ComboBox
		std::function<void(int)>callback() const { return mCallback; }

		void setCallback(const std::function<void(int)>& callback) { mCallback = callback; }

		/// The current index this ComboBox has selected
		int selectedIndex() const { return mSelectedIndex; }

		void setSelectedIndex(int idx);

		/// Sets the items for this ComboBox, providing both short and long descriptive labels
		void setItems(const std::vector<std::string>& items,
			const std::vector<std::string>& itemsShort);

		void setItems(const std::vector<std::string>& items) { setItems(items, items); }

		/// Just for ∂‡Ã¨
		void setLabel(const std::string& label) {}

		/// The short descriptions associated with this ComboBox
		const std::vector<std::string>& items() const { return mItems; }

		const std::vector<std::string>& itemsShort() const { return mItemsShort; }

		///Handles mouse scrolling events for this ComboBox
		virtual bool scrollEvent(const Vector2i& p, const Vector2f& rel) override;


	protected:
		///The items associated with this ComboBox
		std::vector<std::string> mItems;

		///The short description of items associated with this ComboBox/
		std::vector<std::string>mItemsShort;

		///The callback for this ComboBox
		std::function<void(int)> mCallback;

		///The current index this ComboBox has selected
		int mSelectedIndex;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

}