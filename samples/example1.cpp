#include <nanogui/nanogui.h>
//#include <nanogui/screen.h>
//#include <nanogui/formhelper.h>
//#include<nanogui/tabwidget.h>
//#include<nanogui/slider.h>
//#include<nanogui/vscrollpanel.h>
//#include<nanogui/imagepanel.h>
//#include<nanogui/imageview.h>
using namespace nanogui;

enum test_enum {
    Item1 = 0,
    Item2,
    Item3
};



using imagesDataType = std::vector<std::pair<GLTexture, GLTexture::handleType>>;
imagesDataType mImagesData;
int mCurrentImage;

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
        bool bvar = false;
        float fvar = 123123.3f;
        Color colval(0.29f, 0.56f, 0.89f, 1.f);
        FormHelper* gui = new FormHelper(screen);
        ref<Window> window;
        ref<Window> window2;

        window = gui->addWindow(Vector2i(10, 10), "Form helper example");
        window->setLayout(new GroupLayout());

        ///窗口一
        test_enum enumval = Item1;
        gui->addVariable("Enumeration", enumval, enabled)
            ->setItems({ "Item 1", "Item 2", "Item 3" });
        gui->addVariable("bool", bvar);

        //The way to creaete a colorPicker
        gui->addText("This is a useful text! Yerp!", 5/*set Left Margin 5 pixel*/);
        gui->addVariable("Color", colval)
            ->setCallback([&screen](const Color& c) {
            screen->setBackcolor(c);
        });
        //Create a sliderBox
        Label *label1 = new Label(window, "Slider and text box", "sans-bold");
        label1->setLeftMargin(5);
        Widget* panel1 = new Widget(window);
        Slider* slider1 = new Slider(window);
        slider1->setValue(0.5f);
        //slider1->setFixedWidth(80);

        

        /// The TabWidget Window/窗口二
        window = new Window(screen, "Misc. widgets");
        window->setPosition(Vector2i(825, 15));
        window->setLayout(new GroupLayout());

        TabWidget* tabWidget = window->add<TabWidget>();

        Widget* layer = tabWidget->createTab("Function Graph");
        layer->setLayout(new GroupLayout());
        layer->add<Label>("Function graph widget", "sans-bold");

        layer = tabWidget->createTab("Color Wheel");
        layer->setLayout(new GroupLayout());
        layer->add<Label>("Color wheel widget", "sans-bold");
        layer->add<ColorWheel>();



        /// A new window with another layout/窗口三
        window = new Window(screen, "Grid of small widgets");
        window->setPosition(Vector2i(425, 300));
        GridLayout* layout =
            new GridLayout(Orientation::Horizontal, 2,
                Alignment::Middle, 15, 5);
        layout->setColAlignment(
            { Alignment::Maximum, Alignment::Fill });
        layout->setSpacing(0, 10);
        window->setLayout(layout);

        Label* label = new Label(window, "Popup buttons", "sans-bold");
        label->setLeftMargin(5);//设定左边距为5像素
        PopupButton* popupBtn = new PopupButton(window, "Popup", ENTYPO_ICON_EXPORT);
        Popup* popup = popupBtn->popup();
        popup->setLayout(new GroupLayout());
        new Label(popup, "Arbitrary widgets can be placed here");
        new CheckBox(popup, "A check box");

        label = new Label(window, "EnumChoice", "sans-bold");
        label->setLeftMargin(5);//设定左边距为5像素
        ComboBox* combox = new ComboBox(window, { "Item 1", "Item 2", "Item 3" });

        //Create a sliderBox
        label = new Label(window, "BackColor", "sans-bold");
        label->setLeftMargin(5);
        Slider* slider = new Slider(window);
        slider->setValue(100);
        slider->setRange({ 0, 255 });
        slider->setCallback([&screen1](float c) {
            screen1->setBackcolor(Color((int)c,255));
        });



        //Image
        std::vector < std::pair<int, std::string >>
            icons = loadImageDirectory(screen->nvgContext(), "icons");
#if defined(_WIN32)
        std::string resourcesFolderPath("../resources/");
#else
        std::string resourcesFolderPath("./");
#endif


        new Label(window, "Image panel & scroll panel", "sans-bold");
        PopupButton* imagePanelBtn = new PopupButton(window, "Image Panel");
        imagePanelBtn->setIcon(ENTYPO_ICON_FOLDER);
        popup = imagePanelBtn->popup();
        VScrollPanel* vscroll = new VScrollPanel(popup);
        ImagePanel* imgPanel = new ImagePanel(vscroll);
        imgPanel->setImages(icons);
        popup->setFixedSize(Vector2i(245, 150));

        auto imageWindow = new Window(screen, "Selected image");
        imageWindow->setPosition(Vector2i(710, 15));
        imageWindow->setLayout(new GroupLayout());

        // Load all of the images by creating a GLTexture object and saving the pixel data.
        for (auto& icon : icons) {
            GLTexture texture(icon.second);
            auto data = texture.load(resourcesFolderPath + icon.second + ".png");
            mImagesData.emplace_back(std::move(texture), std::move(data));
        }

        // Set the first texture
        auto imageView = new ImageView(imageWindow, mImagesData[0].first.texture());
        mCurrentImage = 0;
        // Change the active textures.
        imgPanel->setCallback([screen, imageView](int i) {
            imageView->bindImage(mImagesData[i].first.texture());
            mCurrentImage = i;
            std::cout << "Selected item " << i << '\n';
        });
        imageView->setGridThreshold(20);
        imageView->setPixelInfoThreshold(20);
        imageView->setPixelInfoCallback(
            [screen, imageView](const Vector2i& index) -> std::pair<std::string, Color> {
            auto& imageData = mImagesData[mCurrentImage].second;
            auto& textureSize = imageView->imageSize();
            std::string stringData;
            uint16_t channelSum = 0;
            for (int i = 0; i != 4; ++i) {
                auto& channelData = imageData[4 * index.y() * textureSize.x() + 4 * index.x() + i];
                channelSum += channelData;
                stringData += (std::to_string(static_cast<int>(channelData)) + "\n");
            }
            float intensity = static_cast<float>(255 - (channelSum / 4)) / 255.0f;
            float colorScale = intensity > 0.5f ? (intensity + 1) / 2 : intensity / 2;
            Color textColor = Color(colorScale, 1.0f);
            return { stringData, textColor };
        });


        //Another way to create a colorPicker without formHelper
        label = new Label(window, "Color picker :", "sans-bold");
        label->setLeftMargin(5);//设定左边距为5像素
        auto cp = new ColorPicker(window, { 255, 120, 0, 255 });
        cp->setFixedSize({ 100, 18 });
        cp->setCallback([&screen](const Color& c) {
            screen->setBackcolor(c);
        });
        CheckBox* cbox = new CheckBox(window, "Don`t Touch me~");
        cbox->setCallback([&screen](bool d) {
            static Color col;
            if (d) {
                col = screen->backColor();
                screen->setBackcolor(Color(0, 0, 0, 0));
            }
            else
                screen->setBackcolor(col);
        });
        /// Set Over 


        /// 窗口四
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
        buttonOne->setLeftMargin(5);//设定bu't'to左边界为5

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
                   
