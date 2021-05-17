#pragma once

#if defined(_WIN32)
#  if defined(NANOGUI_BUILD)
/* Quench a few warnings on when compiling NanoGUI on Windows */
#    pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#    pragma warning(disable : 4244) // warning C4244: conversion from X to Y, possible loss of data
#  endif
#  pragma warning(disable : 4251) // warning C4251: class X needs to have dll-interface to be used by clients of class Y
#  pragma warning(disable : 4714) // warning C4714: function X marked as __forceinline not inlined
#  pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#endif


#include <Eigen/Core>
#include <vector>
#if !defined(NAMESPACE_BEGIN) || defined(DOXYGEN_DOCUMENTATION_BUILD)
    /**
     * \brief Convenience macro for namespace declarations
     *
     * The macro ``NAMESPACE_BEGIN(nanogui)`` will expand to ``namespace
     * nanogui {``. This is done to hide the namespace scope from editors and
     * C++ code formatting tools that may otherwise indent the entire file.
     * The corresponding ``NAMESPACE_END`` macro also lists the namespace
     * name for improved readability.
     *
     * \param name
     *     The name of the namespace scope to open
     */
#define NAMESPACE_BEGIN(name) namespace name {
#endif
#if !defined(NAMESPACE_END) || defined(DOXYGEN_DOCUMENTATION_BUILD)
     /**
      * \brief Convenience macro for namespace declarations
      *
      * Closes a namespace (counterpart to ``NAMESPACE_BEGIN``)
      * ``NAMESPACE_END(nanogui)`` will expand to only ``}``.
      *
      * \param name
      *     The name of the namespace scope to close
      */
#define NAMESPACE_END(name) }
#endif

#if defined(NANOGUI_SHARED)
#  if defined(_WIN32)
#    if defined(NANOGUI_BUILD)
#      define NANOGUI_EXPORT __declspec(dllexport)
#    else
#      define NANOGUI_EXPORT __declspec(dllimport)
#    endif
#  elif defined(NANOGUI_BUILD)
#    define NANOGUI_EXPORT __attribute__ ((visibility("default")))
#  else
#    define NANOGUI_EXPORT
#  endif
#else
      /**
       * If the build flag ``NANOGUI_SHARED`` is defined, this directive will expand
       * to be the platform specific shared library import / export command depending
       * on the compilation stage.  If undefined, it expands to nothing. **Do not**
       * define this directive on your own.
       */
#    define NANOGUI_EXPORT
#endif



// These will produce broken links in the docs build
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

struct NVGcontext { /* Opaque handle type, never de-referenced within NanoGUI */ };
struct GLFWwindow { /* Opaque handle type, never de-referenced within NanoGUI */ };

struct NVGcolor;
struct NVGglyphPosition;
struct GLFWcursor;

#endif // DOXYGEN_SHOULD_SKIP_THIS


//Define command key for windows/mac/linux
#define SYSTEM_COMMAND_MOD GLFW_MOD_CONTROL

namespace nanogui {
    enum class Cursor {
        Arrow = 0,
        IBeam,
        Crosshair,
        Hand,
        HResize,
        VResize,
        CursorCount
    };
    NANOGUI_EXPORT void init();
    NANOGUI_EXPORT void shutdown();
    NANOGUI_EXPORT void mainloop(int refresh);

    /*NANOGUI_EXPORT struct Vector2i {
        int x;
        int y;
    };*/
    //NANOGUI_EXPORT class Color {
    //public:
    //    Color() {
    //        r = 0.3;
    //        g = 0.7;
    //        b = 0.32;
    //        a = 1.0f;
    //    }
    //    Color(float x, float y, float z, float alpha) {
    //        r = x;
    //        g = y;
    //        b = z;
    //        a = alpha;
    //    }
    //    void setColor(float x, float y, float z, float alpha) {
    //        r = x;
    //        g = y;
    //        b = z;
    //        a = alpha;
    //    }
    //    float r;
    //    float g;
    //    float b;
    //    float a;
    //};

    class Color : public Eigen::Vector4f {
        typedef Eigen::Vector4f Base;
    public:
        Color() :Color(0, 0, 0, 0) {}

        Color(const Eigen::Vector4f& color) :Eigen::Vector4f(color) {}

        Color(const Eigen::Vector3f& color, float alpha) :Color(color(0), color(1)
            , color(2), alpha) {}

        Color(const Eigen::Vector3i& color, int alpha) :Color(color.cast<float>() / 255.f,
            alpha / 255.f) {}

        Color(const Eigen::Vector3f& color) : Color(color, 1.0f) {}

        Color(const Eigen::Vector3i& color) : Color((Eigen::Vector3f)(color.cast<float>() / 255.f)) {}

        Color(const Eigen::Vector4i& color)
            :Color((Eigen::Vector4f)(color.cast<float>() / 255.f)) {}

        Color(float intensity, float alpha)
            : Color(Eigen::Vector3f::Constant(intensity), alpha) {}

        Color(int intensity, int alpha) :
            Color(Eigen::Vector3i::Constant(intensity), alpha) {}

        Color(float r, float g, float b, float a) :
            Color(Eigen::Vector4f(r, g, b, a)) {}

        Color(int r, int g, int b, int a) : Color(Eigen::Vector4i(r, g, b, a)) {}

        template<typename Derived> Color(const Eigen::MatrixBase<Derived>& p)
            : Base(p) {}

        template<typename Derived> Color& operator=(const Eigen::MatrixBase<Derived>& p) {
            this->base::operator=(p);
            return *this;
        }

        float& r() { return x(); }

        const float& r()const { return x(); }

        float& g() { return y(); }

        const float& g()const { return y(); }

        float& b() { return z(); }

        const float& b() const{ return z(); }

        Color contrastingColor() const {
            float luminance = cwiseProduct(Color(0.299f, 0.587f, 0.144f, 0.f)).sum();
            return Color(luminance < 0.5f ? 1.f : 0.f, 1.f);
        }

        NANOGUI_EXPORT inline operator const NVGcolor &() const;//From pre-opengl.h
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };


    NANOGUI_EXPORT inline bool nvgIsFontIcon(int value) { return value >= 1024; }//From pre-opengl.h

    using Vector2i = Eigen::Vector2i;
    using Vector2f = Eigen::Vector2f; 
    using Vector3i = Eigen::Vector3i;
    using Vector3f = Eigen::Vector3f;
    using Vector4i = Eigen::Vector4i;
    using Vector4f = Eigen::Vector4f;
    using Matrix3f = Eigen::Matrix3f;
    using Matrix4f = Eigen::Matrix4f;
    using MatrixXf = Eigen::MatrixXf;

    using MatrixXu = Eigen::Matrix < uint32_t, Eigen::Dynamic, Eigen::Dynamic >;

    // skip the forward declarations for the docs
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <typename T> class ref;
    class Layout;
    class Window;
    class Widget;
    class Theme;
    class Screen;
    class Popup;
    class Object;
    class TextBox;
    class Label;
    class Button;
#endif
    /**
     * \brief Convert a single UTF32 character code to UTF8.
     *
     * \rst
     * NanoGUI uses this to convert the icon character codes
     * defined in :ref:`file_nanogui_entypo.h`.
     * \endrst
     *
     * \param c
     *     The UTF32 character to be converted.
     */
    extern NANOGUI_EXPORT std::array<char, 8> utf8(int c);

    /// Load a directory of PNG images and upload them to the GPU (suitable for use with ImagePanel)
    extern NANOGUI_EXPORT std::vector<std::pair<int, std::string>>
        loadImageDirectory(NVGcontext* ctx, const std::string& path);
}


