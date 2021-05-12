#include<nanogui/combobox.h>
#include<nanogui/layout.h>
#include<cassert>

namespace nanogui {

	ComboBox::ComboBox(Widget* parent) : PopupButton(parent), mSelectedIndex(0){}

	ComboBox::ComboBox(Widget* parent, const std::vector<std::string>& items)
		: PopupButton(parent), mSelectedIndex(0)
	{
		setItems(items);
	}

	ComboBox::ComboBox(Widget* parent, const std::vector<std::string>& items,
		const std::vector<std::string>& itemsShort) :
		PopupButton(parent), mSelectedIndex(0) {
		setItems(items, itemsShort);
	}

	void ComboBox::setSelectedIndex(int idx){
		if (mItemsShort.empty())
			return;
		const std::vector<Widget*>& children = popup()->children();
		((Button*)children[mSelectedIndex])->setPushed(false);
		((Button*)children[idx])->setPushed(true);
		mSelectedIndex = idx;
		setCaption(mItemsShort[idx]);
	}


	void ComboBox::setItems(const std::vector<std::string>& items,
		const std::vector<std::string>& itemsShort) {
		assert(items.size() == itemsShort.size());
		mItems = items;
		mItemsShort = itemsShort;
		if (mSelectedIndex < 0 || mSelectedIndex >= (int)items.size())
			mSelectedIndex = 0;
		while (mPopup->childCount() != 0)
			mPopup->removeChild(mPopup->childCount() - 1);
		mPopup->setLayout(new GroupLayout(10));
		int index = 0;
		for (const auto& str : items) {
			Button* button = new Button(mPopup, str);
			button->setFlags(Button::RadioButton);
			button->setCallback([&, index] {
				mSelectedIndex = index;
				setCaption(mItemsShort[index]);
				setPushed(false);
				popup()->setVisible(false);
				if (mCallback)
					mCallback(index);
			});
			index++;
		}
		setSelectedIndex(mSelectedIndex);
	}

	bool ComboBox::scrollEvent(const Vector2i& p, const Vector2f& rel) {
		if (rel.y() < 0) {
			setSelectedIndex(std::min(mSelectedIndex + 1, (int)(items().size() - 1)));
			if (mCallback)
				mCallback(mSelectedIndex);
			return true;
		}
		else if (rel.y() > 0) {
			setSelectedIndex(std::max(mSelectedIndex - 1, 0));
			if (mCallback)
				mCallback(mSelectedIndex);
			return true;
		}
		return Widget::scrollEvent(p, rel);
	}
}