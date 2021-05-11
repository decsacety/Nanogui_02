/*
* \brief Fancy analog widget to selet a color value.  
*/

#pragma once

#include<nanogui/widget.h>

namespace nanogui {

	/*
	* \class ColorWheel colorwheel.h nanogui/colorwheel.h
	* 
	* \brief Fancy analog widget to selet a color value.  
	*/

	class NANOGUI_EXPORT ColorWheel :public Widget {
	public:
		/*
		* Adds a ColorWheel to the specified parent
		* 
		* \param parent 
		*	The Widget to add this ColorWheel to.
		* 
		* \param color
		*	The initial color of the ColotWheel (Default: Red).
		*/
		ColorWheel(Widget* parnet, const Color& color = Color(1.f, 0.f, 0.f, 1.f));

		///The callback to execute when a user changes the ColorWheel value;
		std::function<void(const Color&)> callback() const { return mCallback; }

		void setCallback(const std::function<void(const Color&)>& callback) { mCallback = callback; }

		Color color() const;

		void setColor(const Color& color);

		void setPreSize(const Vector2i size) { preSize = size; }

		virtual Vector2i preferredSize(NVGcontext* ctx) const override;

		virtual void draw(NVGcontext* ctx)override;

		virtual bool mouseButtonEvent(const Vector2i& p, int button, bool down, int mpdifiers) override;

		virtual bool mouseDragEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;



	private:
		//Used to describe where the mouse is interacting
		enum Region {
			None = 0,
			InnerTriangle = 1,
			OuterCircle =2,
			Both =3
		};

		//Convert a specified hue( with saturation = value =1 )to RGN space
		Color hue2rgb(float h) const;

		//Manipulates the positioning of the different regions of the ColorWheel
		Region adjustPosition(const Vector2i& p, Region consideredRegions = Both);

		//personal Value in colorWheel to keep the Wheel with the same size of the Form
		Vector2i preSize;

	protected:
		///The current Hue in the HSV color model
		float mHue;

		/*
		* The implicit Value component of the HSV color model. See implementation
		* \ref nanogui::ColorWheel::Color for its usage. Valid value are in the range
		*  [0.1]
		*/
		float mWhite;

		/*
		* The implicit Value component of the HSV color model. See implementation
		* \ref nanogui::ColorWheel::Color for its usage. Valid value are in the range
		*  [0.1]
		*/
		float mBlack;

		///The current region the mouse is interaction with
		Region mDragRegion;

		///The current callback to execute when the color value has changed 
		std::function<void(const Color&)> mCallback;

	public: 
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};

}