#include <nanogui/common.h>
#include <windows.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <nanogui/screen.h>
#include <map>


namespace nanogui {
    extern std::map<GLFWwindow*, Screen*> __nanogui_screens;//引用声明在screen.h中的__nanogui_screens

    void init()
    {
         glfwSetErrorCallback(
             [](int error, const char* descr) {
             if (error == GLFW_NOT_INITIALIZED)
                 return;
             std::cerr << "GLFW error" << error << ": " << descr << std::endl;
         }
         );

         if (!glfwInit())
             throw std::runtime_error("Could not initialize GLFW!");

         glfwSetTime(0);
         std::cout << "dwad";
    }

    static bool mainloop_active = false;

    void mainloop(int refresh) {

        mainloop_active = true;

        while (mainloop_active) {
            int numScreen = 0;
            for (auto kv : __nanogui_screens) {
                Screen* screen = kv.second;
                if (glfwWindowShouldClose(screen->glfwWindow())) {
                    screen->setVisible(false);
                    continue;
                }
                screen->drawAll();
                numScreen++;
            }

            if (!numScreen)
                mainloop_active = false;

            glfwWaitEvents();
        }

        glfwPollEvents();

    }

    void shutdown() {
        glfwTerminate();
    }

}
