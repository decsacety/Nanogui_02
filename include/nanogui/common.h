#pragma once
#if defined(NANOGUI_SHARED)
#    define NANOGUI_EXPORT __declspec(dllexport)
#  else
#    define NANOGUI_EXPORT __declspec(dllimport)
#  endif

//#pragma once
//#ifdef _DLL
//#    define NANOGUI_EXPORT __declspec(dllexport)
//#  else
//#    define NANOGUI_EXPORT __declspec(dllimport)
//#  endif

NANOGUI_EXPORT struct NVGcontext { /* Opaque handle type, never de-referenced within NanoGUI */ };
NANOGUI_EXPORT struct GLFWwindow { /* Opaque handle type, never de-referenced within NanoGUI */ };

namespace nanogui {

    NANOGUI_EXPORT void init();
    NANOGUI_EXPORT void shutdown();
    NANOGUI_EXPORT void mainloop(int refresh);

    NANOGUI_EXPORT struct Vector2i {
        int x;
        int y;
    };
    NANOGUI_EXPORT class Color {
    public:
        Color() {
            r = 0.3;
            g = 0.7;
            b = 0.32;
            a = 1.0f;
        }
        Color(float x, float y, float z, float alpha) {
            r = x;
            g = y;
            b = z;
            a = alpha;
        }
        void setColor(float x, float y, float z, float alpha) {
            r = x;
            g = y;
            b = z;
            a = alpha;
        }
        float r;
        float g;
        float b;
        float a;
    };

}

