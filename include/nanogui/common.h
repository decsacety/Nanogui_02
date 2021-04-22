#pragma once
#include <Eigen/Core>
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
struct NVGcolor;

namespace nanogui {
    NANOGUI_EXPORT enum class Cursor {
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

    NANOGUI_EXPORT class Color : public Eigen::Vector4f {
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

        Color(int r, int g, int b, int a) : Color(Eigen::Vector4f(r, g, b, a)) {}

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

        NANOGUI_EXPORT inline operator const NVGcolor &() const;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    using Vector2i = Eigen::Vector2i;

    template <typename T> class ref;
    class Layout;
    class Window;
    class Widget;
    class Theme;
    class Screen;
    class Popup;
    class Object;
}

