#include <nanogui/screen.h>
#include <nanogui/formhelper.h>
using namespace nanogui;

int main(int argc, char* argv[])
{
    nanogui::init();

    {
        Screen* screen = nullptr;

        screen = new Screen(Vector2i(1200, 700), "NanoGui-HolyHuaQ!");
         
        Screen* screen1 = new Screen(Vector2i(200, 500), "DiLiDaLiLiDa!!!");
        screen1->setVisible(true); 
        screen1->performLayout();

        //开始创建窗口内容器

        /*Screen* subScreen = new Screen(20, 200, "Form helper example",SUBSCREEN);
        subScreen->setVisible(true);
        subScreen->setParent(screen1);*/

        bool enabled = true;
        int count = 0;
        int ivar = 11111111;//显示数字
        float fvar = 123123.3;
        Color colval(0.29f, 0.56f, 0.89f, 1.f);
        FormHelper* gui = new FormHelper(screen);
        ref<Window> window;
        ref<Window> window2;

        window = gui->addWindow(Vector2i(10, 10), "Form helper example");

        window->setLayout(new GroupLayout());

        Label* label = new Label(window, "Popup buttons", "sans-bold");
        label->setLeftMargin(5);//设定左边距为5像素
        PopupButton* popupBtn = new PopupButton(window, "Popup", ENTYPO_ICON_EXPORT);
        Popup* popup = popupBtn->popup();
        popup->setLayout(new GroupLayout());
        new Label(popup, "Arbitrary widgets can be placed here");

        gui->addText("This is a useful text! Yerp!", 5/*set Left Margin 5 pixel*/);
        gui->addVariable("Color", colval)
            ->setCallback([&screen](const Color& c) {
            screen->setBackcolor(c);
        });


        window2 = gui->addWindow(Vector2i(700, 100), "HuaQ");
        gui->addText("This is a useful text!");
        gui->addText("No matter where you are, it`s still a life.");
        Button* buttonOne =nullptr;
        buttonOne = gui->addButton("A button", [&buttonOne]() {
            buttonOne->setAppendixText(buttonOne->appendixText() + "!");
            std::cout << "Button pressed." << std::endl; /*count++;*/ 
            if (buttonOne->appendixText().size() > 17)
                buttonOne->setAppendixText("HuaQ");
        },"HuaQ");//后面声明的是一个匿名函数作为button的功能。

        Label* appendixLabel = nullptr;
        gui->addButton("A button 1", [&appendixLabel]() {
            static int count = 0 ;
            std::cout << "Button pressed.!!" << std::endl; count++; 
            appendixLabel->setCaption("Count = " + std::to_string(count)); },"Don`t push");
        appendixLabel = gui->addText("Count = " + std::to_string(count));
        gui->addText("This is a useful text!");

        gui->addVariable("Int", ivar)->setSpinnable(true);
        gui->addVariable("Float", fvar);
        //创建完毕


        screen->setVisible(true);
        screen->performLayout();

        //window->setSize(195, 45);
        nanogui::mainloop(0);
    }

    nanogui::shutdown();

    return 0;
}
                   