/*
    src/messagedialog.cpp -- Simple "OK" or "Yes/No"-style modal dialogs

*/

#include<nanogui/messagedialog.h>
#include<nanogui/layout.h>
#include<nanogui/button.h>
#include<nanogui/label.h>

namespace nanogui {

    MessageDialog::MessageDialog(Widget* parent, Type type, const std::string& title,
        const std::string& message,
        const std::string& buttonText,
        const std::string& altButtonText, bool altButton) : Window(parent, title.c_str()) {

        setLayout(new BoxLayout(Orientation::Vertical,
            Alignment::Middle, 10, 10));
        setModal(true);

        Widget* panel1 = new Widget(this);
        panel1->setLayout(new BoxLayout(Orientation::Horizontal,
            Alignment::Middle, 10, 15));

        int icon = 0;
        switch (type) {
        case Type::Information: icon = mTheme->mMessageInformationIcon; break;
        case Type::Question: icon = mTheme->mMessageQuestionIcon; break;
        case Type::Warning: icon = mTheme->mMessageWarningIcon; break;
        }

        Label* iconLabel = new Label(panel1, std::string(utf8(icon).data()), "icons");
        iconLabel->setFontSize(50);
        mMessageLabel = new Label(panel1, message);
        mMessageLabel->setFixedWidth(200);
        Widget* panel2 = new Widget(this);
        panel2->setLayout(new BoxLayout(Orientation::Horizontal,
            Alignment::Middle, 0, 15));

        if (altButton) {
            Button* button = new Button(panel2, altButtonText);
            button->setCallback([&] {
                if (mCallback) mCallback(1); dispose(); });
        }
        Button* button = new Button(panel2, buttonText);
        button->setCallback([&] {
            if (mCallback) mCallback(0); 
            dispose(); });
        button->setTextLeftMargin(10);
        center();
        requestFocus();
    }

}