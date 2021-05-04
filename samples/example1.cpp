#include <nanogui/screen.h>
#include <nanogui/formhelper.h>
using namespace nanogui;

int main(int argc, char* argv[])
{
    nanogui::init();

    {
        Screen* screen = nullptr;

        screen = new Screen(Vector2i(500, 700), "NanoGui-HolyHuaQ!");
         
        Screen* screen1 = new Screen(Vector2i(200, 500), "DiLiDaLiLiDa!!!");
        screen1->setVisible(true); 
        screen1->performLayout();

        //开始创建窗口内容器

        /*Screen* subScreen = new Screen(20, 200, "Form helper example",SUBSCREEN);
        subScreen->setVisible(true);
        subScreen->setParent(screen1);*/

        bool enabled = true;
        int count = 0;
        FormHelper* gui = new FormHelper(screen);
        ref<Window> window;
        ref<Window> window2;

        window = gui->addWindow(Vector2i(10, 10), "Form helper example");
        gui->addText("This is a useful text! Yerp!");

        window2 = gui->addWindow(Vector2i(10, 100), "HuaQ");
        gui->addText("This is a useful text!");
        gui->addText("No matter where you are, it`s still a life.");
        //gui->addButton("A button", [](int& count) { std::cout << "Button pressed." << std::endl; count++; });//后面声明的是一个匿名函数作为button的功能。
        gui->addText("Count = " + std::to_string(count));

        //创建完毕


        screen->setVisible(true);
        screen->performLayout();

        //window->setSize(195, 45);
        nanogui::mainloop(0);
    }

    nanogui::shutdown();

    return 0;
}
                   