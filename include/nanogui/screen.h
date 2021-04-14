#pragma once
#include <nanogui/common.h>
#include <string>

#define SUBSCREEN 0x23131
#define MAINSCREEN 0x31323

namespace nanogui {

    class Screen {

    public:
        //NANOGUI_EXPORT Screen(int wight, int height, const char* name);
        NANOGUI_EXPORT Screen(int wight, int height, const char* name, int sign = MAINSCREEN);
        NANOGUI_EXPORT Screen();

        void initialize(GLFWwindow* window, bool shutdownGLFWOnDestruct);

        NANOGUI_EXPORT void setVisible(bool flag);
        NANOGUI_EXPORT void performLayout();
        NANOGUI_EXPORT void drawAll();
        NANOGUI_EXPORT void setParent(Screen* subScreen);
        GLFWwindow* glfwWindow() { return mGLFWWindow; }

        Color mBackground;
        int sign;
    private:
        GLFWwindow* mGLFWWindow;
        NVGcontext* mNVGContext;
        Vector2i mFBSize;
        Vector2i mSize;
        float mPixelRatio;
        bool mShutdownGLFWOnDestruct;

        bool mVisible;//ÊÇ·ñ¿É¼û

        bool resizeCallbackEvent(int width, int height);
        void drawWidgets();
    };
}