/*
    nanogui/imageview.h -- Widget used to display images.
*/

#pragma once

#include<nanogui/glutil.h>
#include<nanogui/widget.h>
#include<functional>


//#define STB_IMAGE_STATIC
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
// To load image

namespace nanogui {

    /*
    * \class ImageView imageview.h nanogui/imageview.h
    * 
    * \brief Widget used to display images
    */
    class NANOGUI_EXPORT ImageView : public Widget {
    public:
        ImageView(Widget* parent, GLuint imageID);
        ~ImageView();

        void bindImage(GLuint imageId);

        GLShader& imageShader() { return mShader; }

        Vector2f positionF() const { return mPos.cast<float>(); }
        Vector2f sizeF() const { return mSize.cast<float>(); }

        const Vector2i& imageSize() const { return mImageSize; }
        Vector2i scaledImageSize() const { return (mScale * mImageSize.cast<float>()).cast<int>(); }
        Vector2f imageSizeF() const { return mImageSize.cast<float>(); }
        Vector2f scaledImageSizeF() const { return (mScale * mImageSize.cast<float>()); }

        const Vector2f& offset() const { return mOffset; }
        void setOffset(const Vector2f& offset) { mOffset = offset; }
        float scale() const { return mScale; }
        void setScale(float scale) { mScale = scale > 0.0f ? scale : 0.01f; }

        bool fixedOffset() const { return mFixedOffset; }
        void setFixedOffset(bool fo) { mFixedOffset = fo; }//?。。。为什么返回的是bool类型的fixedOffset
        bool fixedScale() const { return mFixedScale; }
        void setFixedScale(bool fixedScale) { mFixedScale = fixedScale; }

        float zoomSensitivity() const { return mZoomSensitivity; }
        void setZoomSensiticity(float tmp) { mZoomSensitivity = tmp; }

        float gridThreshold() const { return mGridThreshold; }
        void setGridThreshold(float gridThreshold) { mGridThreshold = gridThreshold; }

        float pixelInfoThreshold() const { return mPixelInfoThreshold; }
        void setPixelInfoThreshold(float pixelInfo) { mPixelInfoThreshold = pixelInfo; }

#ifndef DOXYGEN_SHOULD_SKIP_THIS 
        void setPixelInfoCallback(const std::function<std::pair<std::string, Color>(const Vector2i&)>& callback) {
            mPixelInfoCallback = callback;
        }
        const std::function<std::pair<std::string, Color>(const Vector2i&)>& pixelInfoCallback() const { return mPixelInfoCallback; }
#endif
         
        void setFontScaleFactor(float fontScaleFactor) { mFontScaleFactor = fontScaleFactor; }
        float fontScaleFactor() const { return mFontScaleFactor; }

        //Image transformation functions 
        
        /// Calucates the image coordinates of the given pixel position on the widget
        Vector2f imageCoordinateAt(const Vector2f& position) const;

        /*
        * Calculate ths image coordinates of the given pixel position on the widget.
        * If the position provided corresponds to a coordinate outsite the range of 
        * the image, the coordinate are clamped to edges of the image
        */
        Vector2f clampedImageCoordinateAt(const Vector2f& position) const;

        /// Calculates the positon inside the widget for the given image coordinate
        Vector2f positionForCoordinate(const Vector2f& imageCoordinate) const;

        /*
        * Modifies the internal state of the image viewer widget so that the pixel at the 
        * position on the widget has the specified image coordinate. Also clamps the value 
        * to the sides of the widget
        */
        void setImageCoordinateAt(const Vector2f& position, const Vector2f& imageCoordinate);
        
        void center();

        void fit();

        void setScaleCentered(float scale);

        void moveOffset(const Vector2f& delta);

        /*
        * Changes the scale factor by the provided amount modified by the zoom sensitivity member varible
        * The scaliing occurs such that the image coordinate under the focused position remeber
        * the same position before and after the scalling
        */
        void zoom(int amount, const Vector2f& focusPosition);

        bool keyboardEvent(int key, int scancode, int action, int modifiers) override;
        bool keyboardCharacterEvent(unsigned int codepoint) override;
        bool mouseDragEvent(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;
        bool scrollEvent(const Vector2i& p, const Vector2f& rel) override;

        /// Function indicating whether the grid is currently visible
        bool gridVisible() const;

        /// Funciton indicating whether the pixel information is currently visible
        bool pixelInfoVisible() const;

        /// Function indicating whething any of the overlays are visible
        bool helpersVisible() const;

        Vector2i preferredSize(NVGcontext* ctx) const override;
        void performLayout(NVGcontext* ctx) override;
        void draw(NVGcontext* ctx) override;


    protected:
        //Helper image methods
        void updateImageParamters();

        //Helper drawing methods
        void drawWidgetBorder(NVGcontext* ctx) const;
        void drawImageBorder(NVGcontext* ctx) const;
        void drawHelpers(NVGcontext* ctx) const;
        static void drawPixelGrid(NVGcontext* ctx, const Vector2f& upperLeftCorner,
            const Vector2f& lowerRightCorner, float stride);
        void drawPixelInfo(NVGcontext* ctx, float stride) const;
        void writePixelInfo(NVGcontext* ctx, const Vector2f& cellPosition,
            const Vector2i& pixel, float stride, float fontSize) const;

        //Image parameters
        GLShader mShader;
        GLuint mImageID;
        Vector2i mImageSize;

        // Image display parameters
        float mScale;
        Vector2f mOffset;
        bool mFixedScale;
        bool mFixedOffset;

        //Fine-tuning paremters
        float mZoomSensitivity = 1.1f;

        // Image info parameters
        float mGridThreshold = -1;
        float mPixelInfoThreshold = -1;

        //Image pixel data display members
        std::function<std::pair<std::string, Color>(const Vector2i&)> mPixelInfoCallback;
        float mFontScaleFactor = .2f;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    //class NANOGUI_EXPORT GLTexture {
    //public:
    //    using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;
    //    GLTexture() = default;
    //    GLTexture(const std::string& textureName)
    //        : mTextureName(textureName), mTextureId(0) {}

    //    GLTexture(const std::string& textureName, GLint textureId)
    //        : mTextureName(textureName), mTextureId(textureId) {}

    //    GLTexture(const GLTexture& other) = delete;
    //    GLTexture(GLTexture&& other) noexcept
    //        : mTextureName(std::move(other.mTextureName)),
    //        mTextureId(other.mTextureId) {
    //        other.mTextureId = 0;
    //    }
    //    GLTexture& operator=(const GLTexture& other) = delete;
    //    GLTexture& operator=(GLTexture&& other) noexcept {
    //        mTextureName = std::move(other.mTextureName);
    //        std::swap(mTextureId, other.mTextureId);
    //        return *this;
    //    }
    //    ~GLTexture() noexcept;

    //    GLuint texture() const { return mTextureId; }
    //    const std::string& textureName() const { return mTextureName; }

    //    /**
    //    *  Load a file in memory and create an OpenGL texture.
    //    *  Returns a handle type (an std::unique_ptr) to the loaded pixels.
    //    */
    //    handleType load(const std::string& fileName);

    //private:
    //    std::string mTextureName;
    //    GLuint mTextureId;
    //};

}