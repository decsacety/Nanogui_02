#include <nanogui/common.h>
#include <iostream>

namespace nanogui {

void init()
{
    std::cout << "nanogui::init" << std::endl;
}

void shutdown()
{
    std::cout << "nanogui::shutdown" << std::endl;
}

}
