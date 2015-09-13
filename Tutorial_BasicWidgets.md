# Widget Introduction #

_Widget_ is the main concept in ui's.
This object inherits from [sf::Drawable](http://www.sfml-dev.org/documentation/1.5/classsf_1_1Drawable.htm), so it can be drawed by a [sf::RenderTarget](http://www.sfml-dev.org/documentation/1.5/classsf_1_1RenderTarget.htm) instance (especially from an [sf::RenderWindow](http://www.sfml-dev.org/documentation/1.5/classsf_1_1RenderWindow.htm) in normal use)
It has a position, a size, a default color for its background and is drawed as a filled-rectangle by default. It can also have widget childrens using STL vector containers.

The root class is a widget but also the GUI frontend ([sf::ui::GuiRenderer](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1GuiRenderer.html)).
It is initialized as the screen size, without color, but can be resized.
The gui renderer also use its own [sf::View](http://www.sfml-dev.org/documentation/1.5/classsf_1_1View.htm) for rendering.

## An example of application ? ##

_main.cpp_
```
#include <SFML/Graphics.hpp>
#include <SFUI.hpp>

using namespace sf;

int main(int ac, char *av[])
{
    RenderWindow myApp(sf::VideoMode(200, 200), "SFML Gui");
    ui::GuiRenderer myGui(myApp); // the frontend widget has a RenderWindow reference.

    // We create a new widget
    ui::Widget myWidget;
    myWidget.SetColor(Color(255, 0, 0));

    myGui.Add(&myWidget); // we add our widget to the gui root widget.

    while (myApp.IsOpened())
    {
        Event event;

        while (myApp.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
                myApp.Close();

            myGui.InjectEvent(event); // widgets processes and propagates events to their hierarchy
        }

        myApp.Clear();

        myGui.Display(); // the renderer use its View for drawing.

        myApp.Display();
    }
}
```

![http://lokk.u7n.org/sfui/sfui_basics1.png](http://lokk.u7n.org/sfui/sfui_basics1.png)

# Other widgets #

There are useful widgets for games applications, with built-in templates.

## [Label](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1Label.html) ##

This object is one of the most used widgets.
It's just an implementation of an sf::String with widget working, but can also have a background color.

```
...
ui::Label myLbl("that's a test");
myLbl.SetX(25);
myLbl.SetTextSize(23.f);

myGui.Add(&myLbl);
...
```

![http://lokk.u7n.org/sfui/sfui_basics2.png](http://lokk.u7n.org/sfui/sfui_basics2.png)

## [Window](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1Window.html) ##

This widget inherits from [sf::ui::MovableWidget](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1MovableWidget.html), so it can be moved to screen.

```
...
ui::Window myWin("My Window");
myWin.SetColor(Color(255, 123, 223));
myWin.SetSize(100, 100);
myWin.SetAlignment(ui::Align::CENTER);

myGui.Add(&myWin);
...
```

![http://lokk.u7n.org/sfui/sfui_basics3.png](http://lokk.u7n.org/sfui/sfui_basics3.png)

## [TextInput](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1TextInput.html) ##

This widget is a common text input line with mouse selection feature.

```
...
ui::TextInput myInput("enter your name...");
myInput.SetWidth(140);
myInput.SetAlignment(ui::Align::CENTER);
myInput.SetColor(Color(123, 123, 123));

myInput.SetSelection(0, 3);
myInput.SetSelectionColor(Color(255, 255, 255, 123));

myGui.SetFocusedWiget(&myInput);
myGui.Add(&myInput);
...
```

![http://lokk.u7n.org/sfui/sfui_basics4.png](http://lokk.u7n.org/sfui/sfui_basics4.png)

## [TextButton](http://lokk.u7n.org/sfui/doc/html/classsf_1_1ui_1_1TextButton.html) ##

This widget is a common button, with built-in style.
For making another button styles, you should read the tutorials about templating.

```
...
ui::TextButton myBtn("Button");
myBtn.SetAlignment(ui::Align::CENTER);

myGui.Add(&myBtn);
...
```

![http://lokk.u7n.org/sfui/sfui_basics5.png](http://lokk.u7n.org/sfui/sfui_basics5.png)