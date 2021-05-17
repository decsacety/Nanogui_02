/*
    nanogui/imagepanel.h -- Image panel widget which shows a number of
    square-shaped icons
*/

#pragma once

#include<nanogui/widget.h>

namespace nanogui {

    /*
    * \calss ImagePanel imagepanel.h nanogui/imagepanel.h
    * 
    * \brief Image panel widget which shows a number of square-shaped icons
    */

    class NANOGUI_EXPORT ImagePanel : public Widget {

    public:
        typedef std::vector<std::pair<int, std::string>> Images;

    public:
        ImagePanel(Widget* parent);

        void setImages(const Images& data) { mImages = data; }
        const Images& images() const { return mImages; }

        std::function<void(int)> callback() const { return mCallback; }
        void setCallback(const std::function<void(int)>& callback) { mCallback = callback; }

        virtual bool mouseMotionEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;
        virtual bool mouseButtonEvent(const Vector2i& p, int button,bool down, int modifiers) override;
        virtual Vector2i preferredSize(NVGcontext* ctx) const override;
        virtual void draw(NVGcontext* ctx) override;

    protected:
        Vector2i gridSize() const;
        int indexForPosition(const Vector2i& p) const;
    protected:
        Images mImages;
        std::function<void(int)> mCallback;
        int mThumbSize;
        int mSpacing;
        int mMargin;
        int mMouseIndex;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

}
