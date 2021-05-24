#include <nanogui/common.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <GLFW/glfw3.h>
#include <nanovg.h>
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
    }

    static bool mainloop_active = false;

    void mainloop(int refresh) {

        mainloop_active = true;

        while (mainloop_active) {
            int numScreen = 0;
            for (auto kv : __nanogui_screens) {
                Screen* screen = kv.second;
                if (!screen->visible())
                    continue;
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

    std::array<char, 8> utf8(int c) {
        std::array<char, 8> seq;
        int n = 0;
        if (c < 0x80) n = 1;
        else if (c < 0x800) n = 2;
        else if (c < 0x10000) n = 3;
        else if (c < 0x200000) n = 4;
        else if (c < 0x4000000) n = 5;
        else if (c < 0x7fffffff) n = 6;
        seq[n] = '\0';
        switch (n) {
            case 6:seq[5] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x4000000;
            case 5:seq[4] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x200000;
            case 4:seq[3] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x10000;
            case 3:seq[2] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x800;
            case 2:seq[1] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x0;
            case 1: seq[0] = c;
        }
        return seq;
    }

    std::vector<std::pair<int, std::string>>
        loadImageDirectory(NVGcontext* ctx, const std::string& path) {
        std::vector<std::pair<int, std::string> > result;
#if !defined(_WIN32)
        DIR* dp = opendir(path.c_str());
        if (!dp)
            throw std::runtime_error("Could not open image directory!");
        struct dirent* ep;
        while ((ep = readdir(dp))) {
            const char* fname = ep->d_name;
#else
        WIN32_FIND_DATA ffd;
        std::string searchPath = path + "/*.*";
        HANDLE handle = FindFirstFileA(searchPath.c_str(), &ffd);
        if (handle == INVALID_HANDLE_VALUE)
            throw std::runtime_error("Could not open image directory!");
        do {
            const char* fname = ffd.cFileName;
#endif
            if (strstr(fname, "png") == nullptr)
                continue;
            std::string fullName = path + "/" + std::string(fname);
            int img = nvgCreateImage(ctx, fullName.c_str(), 0);
            if (img == 0)
                throw std::runtime_error("Could not open image data!");
            result.push_back(
                std::make_pair(img, fullName.substr(0, fullName.length() - 4)));
#if !defined(_WIN32)
        }
        closedir(dp);
#else
        } while (FindNextFileA(handle, &ffd) != 0);
        FindClose(handle);
#endif
        return result;
    }
    inline Color::operator const NVGcolor& () const {
        return reinterpret_cast<const NVGcolor&>(*this->data());
    }

}
