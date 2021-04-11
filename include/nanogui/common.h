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

namespace nanogui {

extern NANOGUI_EXPORT void init();
extern NANOGUI_EXPORT void shutdown();

}
