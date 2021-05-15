/*
* 
*	nanogui/tabwidget.h -- A wrapper around the widgets TabHeader and StackedWidget
*	which hooks the two classes together
* 
*/

#pragma once

#include<nanogui/widget.h>
#include<nanogui/tabheader.h>
#include <nanogui/stactedwidget.h>
#include<functional>

namespace nanogui {

	/*
	*
	*	nanogui/tabwidget.h -- A wrapper around the widgets TabHeader and StackedWidget
	*	which hooks the two classes together
	* 
	* \rst
	*..warning::
	*	
	*	Unlike other widgets, children may **not** be added *directly* to a 
	*	TabWidget. For example, the following code will raise an excaption:
	*	
	*	..code-like::cpp
	*	
	*	//This might be say a nanogui::Screen instance
	*	Winddow * window = new Window(this, "Window Title");
	*	TabWidget *tabWidget = window->add<TabWidget>();
	*	//The label would be a direct child of tabWidget
	*	// which is forbidden, so an exception will be raised 
	*   new Label(tabWidget, "Some Label");
	* 
	*	Instead, you are expected to be creating tabs and adding widgets to those.
	* 
	*	..code-block::cpp
	*	
	*	//This might be say a nanogui::Screen instance
	*	Window *window = new Window(this, "Window Title");
	*	TabWidget *tabWidget = window->add<TabWidget>();
	*	//Create a tab first
	*	auto *layout = tabWidget->createTab("Tab Name");
	*	// Add children to the created tabs
	*	layer->setLayout(new GroupLayout());
	*	new Label(layer, "Some, Label");
	* 
	*	A slightly more involved example of creating a TabWidget can also be found 
	*	in :ref:nanogui_example_1
	* 
	* \endrst
	*
	*/

	class NANOGUI_EXPORT TabWidget :public Widget {
	public:
		TabWidget(Widget* parent);

		/**
		 * \brief Forcibly prevent mis-use of the class by throwing an exception.
		 *        Children are not to be added directly to the TabWidget, see
		 *        the class level documentation (\ref TabWidget) for an example.
		 *
		 * \throws std::runtime_error
		 *     An exception is always thrown, as children are not allowed to be
		 *     added directly to this Widget.
		 */
		virtual void addChild(int index, Widget* widget) override;

		void setActiveTab(int tabIndex);
		int activeTab() const;
		int tabCount() const;

		/*
		* Sets the callable objects which is invoked when a tab is changed
		* The argument provided to the callback is the index of the new active tab;
		*/
		void setCallback(const std::function<void(int)>& callback) { mCallback = callback; }
		const std::function<void(int)>& callback() const { return mCallback; }

		// Create a new tab with the specified name and return a pointer to the layer
		Widget* createTab(const std::string& label);
		Widget* createTab(int index, const std::string& label);

		// Inserts a tab at the tabs collection and associaties it with the provide
		void addTab(const std::string& label, Widget* tab);

		/// Inserts a tab into the tabs collection at the specified index and associates it with
		void addTab(int index, const std::string &label, Widget* tab);

		/*
		* Remove the tab with the specified label and returns the index of the label
		* Returns whether the removal was successful
		*/
		bool removeTab(const std::string& label);

		/// Remove the tab with the specified index
		void removeTab(int index);

		// Retrieves the label of the tab at a specific index
		const std::string& tabLabelAt(int index)const;

		/*
		* Retrieves the index of a specific tab using its tab label
		* Return -1 if there is no such tab
		*/
		int tabLabelIndex(const std::string& label);

		int tabIndex(Widget* tab);

		/*
		* This function can be invoked to ensure that the tab with the provided
		* index is visible to track the tab 
		*/
		void ensureTabVisible(int index);

		/*
		* \brief Retrun a 'const' pointer to the Widget associated with the
		*	specified label
		*/
		const Widget* tab(const std::string& label) const;

		Widget* tab(const std::string& label);

		const Widget* tab(int index) const;

		Widget* tab(int index);

		virtual void performLayout(NVGcontext* ctx) override;
		virtual Vector2i preferredSize(NVGcontext* ctx) const override;
		virtual void draw(NVGcontext* ctx) override;


	private:
		TabHeader* mHeader;
		StackedWidget* mContent;
		std::function<void(int)> mCallback;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	};

}