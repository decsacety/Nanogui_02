#pragma once
#include <nanogui/common.h>
#include <nanogui/widget.h>
#include <GLFW/glfw3.h>
#include <string>

#define SUBSCREEN 0x23131
#define MAINSCREEN 0x31323

namespace nanogui {

    class Screen :public Widget  {

    public:
        //NANOGUI_EXPORT Screen(int wight, int height, const char* name);
        NANOGUI_EXPORT Screen(const Vector2i& size, const char* caption,
            bool resizable = true, bool fullscreen = false, int colorBits = 8,
            int alphaBits = 8, int depthBits = 24, int stencilBits = 8,
            int nSamples = 0);
        NANOGUI_EXPORT Screen();

        void initialize(GLFWwindow* window, bool shutdownGLFWOnDestruct);

        NANOGUI_EXPORT void setVisible(bool flag);
        NANOGUI_EXPORT void setBackcolor(const Color& c) { mBackground = c; }
        NANOGUI_EXPORT void performLayout();
        NANOGUI_EXPORT void drawAll();
        NANOGUI_EXPORT void setParent(Screen* subScreen);
        GLFWwindow* glfwWindow() { return mGLFWWindow; }
        NANOGUI_EXPORT bool cursorPosCallbackEvent(double x, double y);
        NANOGUI_EXPORT bool mouseButtonCallbackEvent(int button, int action, int modifiers);
        NANOGUI_EXPORT bool keyCallbackEvent(int key, int scancode, int action, int mods);
        NANOGUI_EXPORT bool charCallbackEvent(unsigned int codepoint);
        NANOGUI_EXPORT bool dropCallbackEvent(int count, const char** filenames);
        NANOGUI_EXPORT bool scrollCallbackEvent(double x, double y);
        NANOGUI_EXPORT bool resizeCallbackEvent(int width, int height);

        NANOGUI_EXPORT void updateFocus(Widget* widget);
        NANOGUI_EXPORT void drawWidgets();
        NANOGUI_EXPORT void moveWindowToFront(Window* window);

        NANOGUI_EXPORT virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);
        NANOGUI_EXPORT virtual bool keyboardCharacterEvent(unsigned int codepoint);
        NANOGUI_EXPORT virtual bool dropEvent(const std::vector<std::string> &/*filename*/) { return false; /* To be override, now I dont know which function will override it*/ }
    protected:
        GLFWwindow* mGLFWWindow;
        NVGcontext* mNVGContext;
        GLFWcursor* mCursors[(int)Cursor::CursorCount];
        Cursor mCursor;
        std::vector<Widget*> mFocusPath;
        Vector2i mFBSize;
        float mPixelRatio;
        int mMouseState, mModifiers;
        Vector2i mMousePos;
        bool mDragActive;
        Widget* mDragWidget = nullptr;
        double mLastInteraction;
        bool mProcessEvents;
        Color mBackground;
        std::string mCaption;
        bool mShutdownGLFWOnDestruct;
        bool mFullscreen;
        std::function<void(Vector2i)> mResizeCallback; 
    public:
            EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    };
}
