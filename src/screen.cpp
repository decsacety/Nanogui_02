#include <glad/glad.h>
#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/popup.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <nanovg.h>
#ifndef NANOVG_GL3_IMPLEMENTATION
#define NANOVG_GL3_IMPLEMENTATION
#endif
#include <nanovg_gl.h>


namespace nanogui {

    std::map<GLFWwindow*, Screen*> __nanogui_screens;

    static float get_pixel_ratio(GLFWwindow* window) {
        HWND hWnd = glfwGetWin32Window(window);
        HMONITOR monitor = nullptr;
        monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
        static HRESULT(WINAPI * GetDpiForMonitor_)(HMONITOR, UINT, UINT*, UINT*) = nullptr;
        static bool GetDpiForMonitor_tried = false;

        if (!GetDpiForMonitor_tried) {
            auto shcore = LoadLibrary(TEXT("shcore"));
            if (shcore)
                GetDpiForMonitor_tried = true;
        }

        if (GetDpiForMonitor_ && monitor) {
            uint32_t dpiX, dpiY;
            if (GetDpiForMonitor_(monitor, 0, &dpiX, &dpiY) == S_OK)
                return dpiX / 96.0;
        }

        return 1.f;

    }
    void Screen::setParent(Screen* fatherScreen) {
        HWND subHWnd = glfwGetWin32Window(this->mGLFWWindow);
        HWND hWnd = glfwGetWin32Window(fatherScreen->glfwWindow());
        SetWindowLong(subHWnd, GWL_EXSTYLE, WS_VISIBLE | WS_EX_LAYERED);
        //SetWindowLong(subHWnd, GWL_STYLE, GetWindowLong(subHWnd, GWL_STYLE) & (~(WS_CAPTION | WS_SYSMENU | WS_SIZEBOX)));
        MoveWindow(subHWnd, 10, 10, 400, 400, TRUE);
        SetParent(subHWnd, hWnd);
    }
    Screen::Screen() :Widget(nullptr){

    }
    Screen::Screen(const Vector2i& size, const char* name,
        bool resizable, bool fullscreen, int colorBits,
        int alphaBits, int depthBits, int stencilBits,
        int nSamples):Widget(nullptr), mGLFWWindow(nullptr), mNVGContext(nullptr),
        mCursor(Cursor::Arrow), mBackground(0.45f, 0.549f, 0.6f, 1.f), mCaption(name),
        mShutdownGLFWOnDestruct(false), mFullscreen(fullscreen)
    {
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mGLFWWindow = glfwCreateWindow(size[0], size[1], name, nullptr, nullptr);

        if (!mGLFWWindow)
            std::cout << "Fail to create an OpenGL context !";

        glfwMakeContextCurrent(mGLFWWindow);//初始化及创建窗口

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Could not initialize GLAD!");//初始化glad

        glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);
        glViewport(0, 0, mFBSize[0], mFBSize[1]);
        glClearColor(mBackground[0], mBackground[1], mBackground[2], mBackground[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwSwapInterval(0);
        glfwSwapBuffers(mGLFWWindow);//背景视口等设置完毕， 开始设置回调函数

        glfwSetCursorPosCallback(mGLFWWindow,
            [](GLFWwindow* w, double x, double y) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->cursorPosCallbackEvent(x, y);
        }
        );

        glfwSetMouseButtonCallback(mGLFWWindow,
            [](GLFWwindow* w, int button, int action, int modifiers) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->mouseButtonCallbackEvent(button, action, modifiers);
        }
        );

        glfwSetKeyCallback(mGLFWWindow,
            [](GLFWwindow* w, int key, int scancode, int action, int mods) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->keyCallbackEvent(key, scancode, action, mods);
        }
        );

        glfwSetCharCallback(mGLFWWindow,
            [](GLFWwindow* w, unsigned int codepoint) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->charCallbackEvent(codepoint);
        }
        );

        glfwSetDropCallback(mGLFWWindow,
            [](GLFWwindow* w, int count, const char** filenames) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->dropCallbackEvent(count, filenames);
        }
        );

        glfwSetScrollCallback(mGLFWWindow,
            [](GLFWwindow* w, double x, double y) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;
            if (!s->mProcessEvents)
                return;
            s->scrollCallbackEvent(x, y);
        }
        );

        //帧大小事件
        glfwSetFramebufferSizeCallback(mGLFWWindow,
            [](GLFWwindow *w, int width, int height) {
            auto it = __nanogui_screens.find(w);
            if (it == __nanogui_screens.end())
                return;
            Screen* s = it->second;

            s->resizeCallbackEvent(width, height);
        }
        );

        //notify if windows focus
        glfwSetWindowFocusCallback(mGLFWWindow,
            [](GLFWwindow* w, int focused) {
                auto it = __nanogui_screens.find(w);
                if (it == __nanogui_screens.end())
                    return;
                Screen* s = it->second;
                s->focusEvent(focused != 0);
            }
        );

        initialize(mGLFWWindow, true);
    }

    void Screen::initialize(GLFWwindow* window, bool shutdownGLFWOnDestruct) {
        mGLFWWindow = window;
        mShutdownGLFWOnDestruct = shutdownGLFWOnDestruct;
        glfwGetWindowSize(mGLFWWindow, &mSize[0], &mSize[1]);
        glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);

        mPixelRatio = get_pixel_ratio(window);//

        if (mPixelRatio != 1)
            glfwSetWindowSize(window, mSize[0] * mPixelRatio, mSize[1] * mPixelRatio);//
        
        GLint nStencilBits = 0, nSamples = 0;
        glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
            GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &nStencilBits);
        glGetIntegerv(GL_SAMPLES, &nSamples);

        int flags = 0;
        if (nStencilBits >= 8)
            flags |= NVG_STENCIL_STROKES;
        if (nSamples <= 1)
            flags |= NVG_ANTIALIAS;

        mNVGContext = nvgCreateGL3(flags);
        if (mNVGContext == nullptr)
            std::cout << "Could not initialize NanoVG";

        mVisible = glfwGetWindowAttrib(window, GLFW_VISIBLE) != 0;
        setTheme(new Theme(mNVGContext));
        mMousePos = Vector2i::Zero();
        mMouseState = mModifiers = 0;
        mDragActive = false;
        mLastInteraction = glfwGetTime();
        mProcessEvents = true;
        __nanogui_screens[mGLFWWindow] = this;

        nvgBeginFrame(mNVGContext, mSize[0], mSize[1], mPixelRatio);
        nvgEndFrame(mNVGContext);
    }

    void Screen::drawAll() {
        //if (!mVisible)
        //    return;
        //glfwMakeContextCurrent(mGLFWWindow);//切换opengl上下文

        glClearColor(mBackground[0], mBackground[1], mBackground[2], mBackground[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        drawWidgets();

        glfwSwapBuffers(mGLFWWindow);
    }

    void Screen::drawWidgets() {
        if (!mVisible)
            return;
        glfwMakeContextCurrent(mGLFWWindow);//切换opengl上下文
        
        glfwGetFramebufferSize(mGLFWWindow, &mFBSize[0], &mFBSize[1]);
        glfwGetWindowSize(mGLFWWindow, &mSize[0], &mSize[1]);

        mSize = (mSize.cast<float>() / mPixelRatio).cast<int>();
        mFBSize = (mSize.cast<float>() * mPixelRatio).cast<int>();

        glViewport(0, 0, mFBSize[0], mFBSize[1]);
        glBindSampler(0, 0);
        nvgBeginFrame(mNVGContext, mSize[0], mSize[1], mPixelRatio);

        draw(mNVGContext);

        double elapsed = glfwGetTime() - mLastInteraction;
        
        nvgEndFrame(mNVGContext);
    }

    bool Screen::keyboardEvent(int key, int scancode, int action, int modifiers) {
        if (mFocusPath.size() > 0) {
            for(auto it = mFocusPath.rbegin()+1;it!= mFocusPath.rend();it++)
                if((*it)->focused()&&(*it)->keyboardEvent(key, scancode, action, modifiers))
                    return true;
        }
        return false;
    }

    bool Screen::keyboardCharacterEvent(unsigned int codepoint) {
        if (mFocusPath.size() > 0) {
            for (auto it = mFocusPath.rbegin() + 1; it != mFocusPath.rend(); ++it)
                if((*it)->focused() && (*it)->keyboardCharacterEvent(codepoint))
                    return true;
        }
        return false;
    }

    bool Screen::cursorPosCallbackEvent(double x, double y) {
        Vector2i p((int)x, (int)y);

        p = (p.cast<float>() / mPixelRatio).cast<int>();

        bool ret = false;
        mLastInteraction = glfwGetTime();
        try {
            p -= Vector2i(1, 2);

            if (!mDragActive) {
                Widget* widget = findWidget(p);
                if (widget != nullptr && widget->cursor() != mCursor) {
                    mCursor = widget->cursor();
                    glfwSetCursor(mGLFWWindow, mCursors[(int)mCursor]);
                }
            }
            else {
                ret = mDragWidget->mouseDragEvent(
                    p - mDragWidget->parent()->absolutePosition(), p - mMousePos,
                    mMouseState, mModifiers);
            }

            if (!ret)
                ret = mouseMotionEvent(p, p - mMousePos, mMouseState, mModifiers);

            mMousePos = p;

            return ret;
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
            return false;
        }
    }

    bool Screen::mouseButtonCallbackEvent(int button, int action, int modifiers) {
        
        //检测双击事件
        static bool doubleClick = false;
        static double lastTime = glfwGetTime();
        bool isDoubleClick = false;
        if ((glfwGetTime() - lastTime < 0.3) && doubleClick == true&& action == GLFW_PRESS) {
            if (mouseButtonEvent(mMousePos, button, action == GLFW_PRESS,
                mModifiers)) {
                modifiers = 12;
                isDoubleClick = true;
            }
        }

        mLastInteraction = glfwGetTime();
        mModifiers = modifiers;
        
        try {
            if (mFocusPath.size() > 1) {
                const Window* window =
                    dynamic_cast<Window *>(mFocusPath[mFocusPath.size() - 2]);
                if (window && window->modal()) {
                    if (!window->contains(mMousePos))
                        return false;
                }
            }

            if (action == GLFW_PRESS) {
                mMouseState |= 1 << button;
            }
            else {
                doubleClick = !doubleClick;
                lastTime = glfwGetTime();
                mMouseState &= ~(1 << button);
            }

            auto dropWidget = findWidget(mMousePos);
            if (mDragActive && action == GLFW_RELEASE && dropWidget != mDragWidget)
                mDragWidget->mouseButtonEvent(
                    mMousePos - mDragWidget->parent()->absolutePosition(), button,
                    false, mModifiers);

            if (dropWidget != nullptr && dropWidget->cursor() != mCursor) {
                mCursor = dropWidget->cursor();
                glfwSetCursor(mGLFWWindow, mCursors[(int)mCursor]);
            }

            if (action == GLFW_PRESS && (button == GLFW_MOUSE_BUTTON_1
                || button == GLFW_MOUSE_BUTTON_2)) {
                mDragWidget = findWidget(mMousePos);
                if (mDragWidget == this)
                    mDragWidget = nullptr;
                mDragActive = mDragWidget != nullptr;
                if (!mDragActive)
                    updateFocus(nullptr);
            }
            else {
                mDragActive = false;
                mDragWidget = nullptr;
            }

            return mouseButtonEvent(mMousePos, button, action == GLFW_PRESS,
                mModifiers);
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception in event in handler: " << e.what() << std::endl; 
            return false;
        }
    }

    bool Screen::keyCallbackEvent(int key, int scancode, int action, int mods) {
        mLastInteraction = glfwGetTime();
        try {
            return keyboardEvent(key, scancode, action, mods);
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
            return false;
        }
    }

    bool Screen::charCallbackEvent(unsigned int codepoint) {
        mLastInteraction = glfwGetTime();
        try {
            return keyboardCharacterEvent(codepoint);
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception in event handler: " << e.what() << std::endl;
            return false;
        }
    }

    bool Screen::dropCallbackEvent(int count, const char** filenames) {
        std::vector<std::string> arg(count);
        for (int i = 0; i < count; ++i)
            arg[i] = filenames[i];
        return dropEvent(arg);
    }

    bool Screen::scrollCallbackEvent(double x, double y) {
        mLastInteraction = glfwGetTime();
        try{
            if (mFocusPath.size() > 1) {
                const Window* window =
                    dynamic_cast<Window*>(mFocusPath[mFocusPath.size() - 2]);
                if (window && window->modal()) {
                    if (!window->contains(mMousePos))
                        return false;
                }
            }
            return scrollEvent(mMousePos, Eigen::Vector2f(x, y));
        }
        catch (const std::exception& e) {
            std::cerr << "Caught excetion in event handler: " << e.what() << std::endl;
            return false; 
        }
    }

    bool Screen::resizeCallbackEvent(int width, int height) {
        //Vector2i fbSize, size;
        glViewport(0, 0, width, height);
        // glfwGetFramebufferSize(mGLFWWindow, &fbSize.x, &fbSize.y);
         //glfwGetWindowSize(mGLFWWindow, &size.x, &size.y);


        return true;
    }

    void Screen::updateFocus(Widget* widget) {
        for (auto w : mFocusPath) {
            if (!w->focused())
                continue;
            w->focusEvent(false);
        }
        mFocusPath.clear();
        Widget* window = nullptr;
        while (widget) {
            mFocusPath.push_back(widget);
            if (dynamic_cast<Window*> (widget))
                window = widget;
            widget = widget->parent();
        }
        for (auto it = mFocusPath.rbegin(); it != mFocusPath.rend(); ++it)
            (*it)->focusEvent(true);

        if (window)
            moveWindowToFront((Window*)window);
    }

    void Screen::moveWindowToFront(Window* window) {
        mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), window), mChildren.end());
        mChildren.push_back(window);

        bool changed = false;
        do {
            size_t baseIndex = 0;
            for (size_t index = 0; index < mChildren.size(); ++index)
                if (mChildren[index] == window)
                    baseIndex = index;
            changed = false;
            for (size_t index = 0; index < mChildren.size(); ++index) {
                Popup* pw = dynamic_cast<Popup*>(mChildren[index]);
                if (pw && pw->parentWindow() == window && index < baseIndex) {
                    moveWindowToFront(pw);
                    changed = true;
                    break;
                }
            }
        } while (changed);
    }

    void Screen::setVisible(bool flag) {
        if (mVisible != flag) {
            mVisible = flag;

            if (mVisible)
                glfwShowWindow(mGLFWWindow);
            else
                glfwHideWindow(mGLFWWindow);
        }
    }
    void Screen::performLayout() {
        Widget::performLayout(mNVGContext);
    }
}