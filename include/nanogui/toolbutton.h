/*
    nanogui/toolbutton.h -- Simple radio+toggle button with an icon
*/

#pragma once 

#include <nanogui/button.h>

namespace nanogui {

    class ToolButton :public Button {
    public:
        ToolButton(Widget* parent, int icon,
            const std::string& caption = "") :
            Button(parent, caption, icon) {
            setFlags(Flags::RadioButton | Flags::ToggleButton);
            setFixedSize(Vector2i(25, 25));
        }
    };
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

}