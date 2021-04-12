#pragma once
#include <nanogui/common.h>
#include <string>

namespace nanogui {

    class Screen {

    public:
        NANOGUI_EXPORT Screen(int wight, int height, const char* name);
        NANOGUI_EXPORT Screen();

        void initialize(GLFWwindow* window, bool shutdownGLFWOnDestruct);

        NANOGUI_EXPORT void setVisible(bool flag);
        NANOGUI_EXPORT void performLayout();
        NANOGUI_EXPORT void drawAll();
        GLFWwindow* glfwWindow() { return mGLFWWindow; }

        Color mBackground;
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