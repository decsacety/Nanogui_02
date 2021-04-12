#include <glad/glad.h>
#include <nanogui/screen.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<map>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

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

    Screen::Screen() {

    }
    Screen::Screen(int wight, int height, const char* name):mBackground(0.3f, 0.3f, 0.32f, 1.f)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mGLFWWindow = glfwCreateWindow(wight, height, name, nullptr, nullptr);

        if (!mGLFWWindow)
            std::cout << "Fail to create an OpenGL context !";

        glfwMakeContextCurrent(mGLFWWindow);//初始化及创建窗口

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Could not initialize GLAD!");//初始化glad

        glfwGetFramebufferSize(mGLFWWindow, &mFBSize.x, &mFBSize.y);
        glViewport(0, 0, mFBSize.x, mFBSize.y);
        glClearColor(mBackground.r, mBackground.g, mBackground.b, mBackground.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glfwSwapInterval(0);
        glfwSwapBuffers(mGLFWWindow);//背景视口等设置完毕， 开始设置回调函数

        glfwSetCursorPosCallback(mGLFWWindow,
            [](GLFWwindow* w, double x, double y) {

        }
        );

        glfwSetMouseButtonCallback(mGLFWWindow,
            [](GLFWwindow* w, int button, int action, int modifiers) {

        }
        );

        glfwSetKeyCallback(mGLFWWindow,
            [](GLFWwindow* w, int key, int scancode, int action, int mods) {

        }
        );

        glfwSetCharCallback(mGLFWWindow,
            [](GLFWwindow* w, unsigned int codepoint) {

        }
        );

        glfwSetDropCallback(mGLFWWindow,
            [](GLFWwindow* w, int count, const char** filenames) {

        }
        );

        glfwSetScrollCallback(mGLFWWindow,
            [](GLFWwindow* w, double x, double y) {

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

        }
        );

        initialize(mGLFWWindow, true);
    }

    void Screen::initialize(GLFWwindow* window, bool shutdownGLFWOnDestruct) {
        mGLFWWindow = window;
        mShutdownGLFWOnDestruct = shutdownGLFWOnDestruct;
        glfwGetWindowSize(mGLFWWindow, &mSize.x, &mSize.y);
        glfwGetFramebufferSize(mGLFWWindow, &mFBSize.x, &mFBSize.y);

        mPixelRatio = get_pixel_ratio(window);//

        if (mPixelRatio != 1)
            glfwSetWindowSize(window, mSize.x * mPixelRatio, mSize.y * mPixelRatio);//
        
        GLint nStencilBits = 0, nSamples = 0;
        glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
            GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &nStencilBits);
        glGetIntegerv(GL_SAMPLES, &nSamples);

        __nanogui_screens[mGLFWWindow] = this;

    }

    void Screen::drawAll() {
        glClearColor(mBackground.r, mBackground.g, mBackground.b, mBackground.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        drawWidgets();

        glfwSwapBuffers(mGLFWWindow);
    }

    void Screen::drawWidgets() {
        if (!mVisible)
            return;

        glfwMakeContextCurrent(mGLFWWindow);//切换opengl上下文

        glfwGetFramebufferSize(mGLFWWindow, &mFBSize.x, &mFBSize.y);
        glfwGetWindowSize(mGLFWWindow, &mSize.x, &mSize.y);

        //glViewport(0, 0, mFBSize.x, mFBSize.y);
        
    }

    bool Screen::resizeCallbackEvent(int width, int height) {
        Vector2i fbSize, size;
        glViewport(0, 0, width, height);
        // glfwGetFramebufferSize(mGLFWWindow, &fbSize.x, &fbSize.y);
         //glfwGetWindowSize(mGLFWWindow, &size.x, &size.y);


        return true;
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

    }
}