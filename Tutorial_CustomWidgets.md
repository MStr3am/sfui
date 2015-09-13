# Widget construction #

This tutorial will show you how to create a new widget (or a group of widgets) and make it simple and robust using SFUI's tools.

We have to examine two points of view : widget structure and widget design (with styles)
Ok, I choose to make a simple ConfirmBox widget, so... let's go !

## The structure ##

Our `ConfirmBox` class will be a window with a label for text information and two buttons (cancel, ok) on it.

`ConfirmBox.hpp`
```
#ifndef MYCONFIRMBOX_HPP
#define MYCONFIRMBOX_HPP

#include "Window.hpp"
#include "TextButton.hpp"

namespace sf
{
    namespace ui
    {
        class ConfirmBox : public Window // Inherits from the default window widget
        {
            public :
                /* The constructor take the necessary values in argument */
                ConfirmBox(const Unicode::Text& title, const Unicode::Text& info);

            protected :
                Label           mInfoLbl;
                TextButton      mOkBtn;
                TextButton      mCancelBtn;
        };
    }
}
#endif // MYCONFIRMBOX_HPP
```
`ConfirmBox.cpp`
```

#include "ConfirmBox.hpp"

namespace sf
{
    namespace ui
    {
        ConfirmBox::ConfirmBox(const Unicode::Text& title, const Unicode::Text& info)
            :   Window(title),        // First, we initialize the window
                mInfoLbl(info),       // and the other widgets...
                mOkBtn("Ok"),
                mCancelBtn("Cancel")
        {
            /* Then we have to add the childrens to the box ;) */
            Add(&mInfoLbl);
            Add(&mOkBtn);
            Add(&mCancelBtn);
        }
    }
}
```

You shouldn't have any problems with the code above.<br />It's very simple to create an instance of it, like other widgets :
```
sf::ui::ConfirmBox myBox("Warning !", "Do you really want to change the current skin ?\nIt will be destroyed...");
myGui.Add(&myBox);
```

Ok... Try to compile and execute it.<br />
Arghhh, rendering is chaotic, but it is normal : all widgets have the position 0/0.

## Design part ##
Now, there are at least two different ways to position them on the box.
  1. Positioning in the constructor (hard-coded)
  1. Positioning using styles

Obviously, it makes sense to use the second way for this tutorial, because of advanced usage of styles.

First, we want to add a built-in style to our ConfirmBox. Just add this code in the constructor :
```
SetDefaultStyle("MyConfirmBox");
LoadStyle(GetDefaultStyle()); // and we load it !
```

Ok, so we can now modify the box by style, but how control children styles ? (which are in protected state anyway...)<br />
It will be useful to access them by something like "MyConfirmBox>Info" in the xml file.

That hierarchy must be processed by masking the public virtual method `LoadStyle(...)` :
```
virtual void ConfirmBox::LoadStyle(const std::string& nameStyle)
{
    mInfoLbl.LoadStyle(nameStyle + "->Info");
    mOkBtn.LoadStyle(nameStyle + "->Ok");
    mCancelBtn.LoadStyle(nameStyle + "->Cancel");

    Window::LoadStyle(nameStyle);
}
```
You can now create your style file =)
```
<style name="MyConfirmBox" width="320" height="120" align="center" color="rgba: 255, 123, 233, 123" />
<style name="MyConfirmBox->Title" textSize="23" textColor="#000000" align="top_center" />
<style name="MyConfirmBox->Info" x="10" y="40" />
<style name="MyConfirmBox->Ok" align="bottom_right" x="-10" y="-10" />
<style name="MyConfirmBox->Cancel" align="bottom_right" x="-80" y="-10" />
```
![http://lokk.u7n.org/sfui/sfui_widgetdesign1.png](http://lokk.u7n.org/sfui/sfui_widgetdesign1.png)

Tadaaam !
The next part of this tutorial will deal with dynamic properties for advanced widgets.