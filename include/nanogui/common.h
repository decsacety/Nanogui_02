#pragma once
#if defined(NANOGUI_SHARED)
#  if defined(NANOGUI_BUILD)
#    define NANOGUI_EXPORT __declspec(dllexport)
#  else
#    define NANOGUI_EXPORT __declspec(dllimport)
#  endif
#else
#  define NANOGUI_EXPORT
#endif

//#pragma once
//#ifdef _DLL
//#    define NANOGUI_EXPORT __declspec(dllexport)
//#  else
//#    define NANOGUI_EXPORT __declspec(dllimport)
//#  endif

NANOGUI_EXPORT struct NVGcontext { /* Opaque handle type, never de-referenced within NanoGUI */ };
NANOGUI_EXPORT struct GLFWwindow { /* Opaque handle type, never de-referenced within NanoGUI */ };

namespace nanogui {

    extern NANOGUI_EXPORT void init();
    extern NANOGUI_EXPORT void shutdown();
    NANOGUI_EXPORT struct Vector2i {
        int x;
        int y;
    };

}

