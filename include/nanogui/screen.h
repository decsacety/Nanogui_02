#include <glad/glad.h>
#include <nanogui/common.h>
#include <string>

namespace nanogui {
    class Screen {

    public:
        NANOGUI_EXPORT Screen(int wight, int height, const char* name);
        NANOGUI_EXPORT Screen();
        NANOGUI_EXPORT void setVisible(bool flag);
        NANOGUI_EXPORT void performLayout();

    private:
        GLFWwindow* mGLFWWindow;
        NVGcontext* mNVGContext;
        Vector2i mFBSize;
    };
}