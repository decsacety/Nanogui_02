#include<nanogui/screen.h>
#include<nanogui/window.h>
#include<nanogui/object.h>
#include<nanogui/widget.h>

namespace nanogui {
	NANOGUI_EXPORT class FormHelper {
	public: 
		FormHelper(Screen* screen) : mScreen(screen){}

		Window* addWindow(int posx,int posy , const char* title = "NoName")
		{
			mWindow = new Window(mScreen, title);
			//mWindow = new Window(mScreen, title);
		}
	protected:
		ref<Screen> mScreen;
		ref<Window> mWindow/*;
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW*/
	};
}