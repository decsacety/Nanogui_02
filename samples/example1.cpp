#include <nanogui/common.h>
#include <nanogui/screen.h>
using namespace nanogui;

int main(int argc, char* argv[])
{
    nanogui::init();

    {
        Screen* screen = nullptr;

        screen = new Screen(500, 700, "NanoGui-HolyFuck£¿");

        screen->setVisible(true);
        screen->performLayout();
    }

    nanogui::shutdown();

    return 0;
}
