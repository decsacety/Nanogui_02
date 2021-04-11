#include <nanogui/screen.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<map>

namespace nanogui {

    std::map<GLFWwindow*, Screen*> __nanogui_screens;

    Screen::Screen() {

    }
    Screen::Screen(int wight, int height, const char* name)
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
        glClearColor(0.3f, 0.3f, 0.32f, 1.f);
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

        getchar();

    }
    void Screen::setVisible(bool flag) {

    }
    void Screen::performLayout() {

    }
}