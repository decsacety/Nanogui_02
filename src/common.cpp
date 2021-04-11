#include <nanogui/common.h>
#include <windows.h>
#include <GLFW/glfw3.h>
#include <iostream>


namespace nanogui {

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

    void shutdown() {
        glfwTerminate();
    }

}
