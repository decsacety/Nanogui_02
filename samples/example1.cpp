#include <nanogui/common.h>
#include <nanogui/screen.h>
#include <nanogui/formhelper.h>
using namespace nanogui;

int main(int argc, char* argv[])
{
    nanogui::init();

    {
        Screen* screen = nullptr;

        screen = new Screen(500, 700, "NanoGui-HolyHuaQ!");
         
        Screen* screen1 = new Screen(200, 500, "DiLiDaLiLiDa!!!");
        screen1->setVisible(true);

        //��ʼ��������������
        bool enabled = true;
        FormHelper* gui = new FormHelper(screen);
        //ref<Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");

        //�������


        screen->setVisible(true);
        screen->performLayout();

        nanogui::mainloop(0);
    }

    nanogui::shutdown();

    return 0;
}
