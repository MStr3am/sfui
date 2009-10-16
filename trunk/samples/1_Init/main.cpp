
#include <SFML/Graphics.hpp>
#include <SFUI.hpp>

int main(int ac, char **av)
{
    // First we create our SFML context rendering.
    sf::RenderWindow myApp(sf::VideoMode(800, 600), "Demo Init");

    // Then we create the Gui renderer (by passing it the context target reference)
    sf::ui::GuiRenderer myGui(myApp);

    while (myApp.IsOpened())
    {
        sf::Event event;

        while (myApp.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
	                myApp.Close();

            // Events are also injected to widget hierarchy (for widget listeners)
            myGui.InjectEvent(event);
        }

        myApp.Clear();

        // Here, we draw the user interface (with sf::View internal access)
        myGui.Display();

        myApp.Display();
    }

    return (EXIT_SUCCESS);
}
