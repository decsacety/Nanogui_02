# Nanogui_02
GUI with nanogui`s core and ImGui` style 
Using the core solution and add some new charactor of ImGui .
Now you can insert some subwindows and change their format or transparent as you like.

这是一个基于nanogui核心源码和ImGui风格改写的GUI库。  
由于是从0开始一行一行搭建的，所以在很多细节上和原本的nanogui不一致，继承了其核心的OOD思路，以及增加了一些新的特性  


相较于原本的nanogui  
GUI界面方面：
新增了右键扩展窗体大小的功能。  
新增了textBox控件随内容长度变化而自动扩展的功能  
修改了popup控件的款式  
新增了comboBox的排布  
增加了双击Titile折叠窗体的功能  
etc.

新增了button控件同行文本的显示，可以通过在button的创建函数中添加appendixText=“”来创建button同行文本  
新增了可以通过在Formhelper中可以通过在addText函数末尾添加int来指定Text左边界的功能  
修复了screen.cpp里drawAll函数中先刷新背景颜色再切换OpenGL上下文的错误  
修改了checkBox的icon表达方式    
etc.

It looks like now :
![Image text](https://github.com/decsacety/Nanogui_02/blob/main/samples/n1.png)
![Image text](https://github.com/decsacety/Nanogui_02/blob/main/samples/n2.png)
![Image text](https://github.com/decsacety/Nanogui_02/blob/main/samples/n3.png)

