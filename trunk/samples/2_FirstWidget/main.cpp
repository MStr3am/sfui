
#include <SFML/Graphics.hpp>
#include <SFUI.hpp>

using namespace sf;

int main(int ac, char **av)
{
    RenderWindow myApp(VideoMode(800, 600), "Demo Widget");

    ui::GuiRenderer myGui(myApp);

    // We create a new very basic widget (just a rectangle on screen)
    ui::Widget myFirstWidget;

    // We set a few properties...
    myFirstWidget.SetSize(360, 412);
    myFirstWidget.SetColor(Color(223, 13, 123));
    myFirstWidget.SetAlignment(ui::Align::CENTER);

    // Finally, we add this widget to our gui top container.
    myGui.GetTopWidget().Add(&myFirstWidget);

    while (myApp.IsOpened())
    {
        Event event;

        while (myApp.GetEvent(event))
        {
            if (event.Type == Event::Closed)
                myApp.Close();

            myGui.InjectEvent(event);
        }

        myApp.Clear();

        // We don't need to do anything here...
        myGui.Display();

        myApp.Display();
    }

    return (EXIT_SUCCESS);
}
