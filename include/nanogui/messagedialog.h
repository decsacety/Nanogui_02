/*
    nanogui/messagedialog.h -- Simple "OK" or "Yes/No"-style modal dialogs
*/

#pragma once

#include <nanogui/window.h>

namespace nanogui {

    /*
    * \ class MessageDialog.h nanogui/messagedialog.h
    * 
    * \brief Simple "OK" or "YES/NO"-style modal dialogs
    */

    class NANOGUI_EXPORT MessageDialog : public Window {
    public:
        /// Classification of the type of message this MessageDialog represents
        enum class Type {
            Information,
            Question,
            Warning
        };

        MessageDialog(Widget* parent, Type type, const std::string& title = "Untitled",
            const std::string& message = "Message",
            const std::string& buttonText = "OK",
            const std::string& altButtonText = "Cancel",
            bool altButton = false);

        Label* messageLabel() { return mMessageLabel; }
        const Label* messgaeLabel() const { return mMessageLabel; }

        std::function<void(int)> callback()const { return mCallback; }
        void setCallback(const std::function<void(int)>& callback) { mCallback = callback; }

    protected:
        std::function<void(int)> mCallback;
        Label* mMessageLabel;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

}