/*
    This file is part of ReGen (by Robin RUAUX).

    ReGen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ReGen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ReGen.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <SFML/Graphics.hpp>
#include "GuiRenderer.hpp"
#include <iostream>

#include "Button.hpp"

int     main(int ac, char **av)
{
    sf::RenderWindow    App(sf::VideoMode(800, 600), "SFML Gui");
    sf::GuiRenderer     Gui(App);

    sf::Button  btn("Play"), btn2("Stop");
    btn.SetColor(sf::Color(123, 123, 123, 125));
    btn.SetPosition(100, 120);

    btn2.SetColor(sf::Color(123, 123, 123));
    btn2.SetPosition(350, 256);

    sf::Widget& top = Gui.GetTopWidget();
    top.Add(&btn);
    top.Add(&btn2);


    App.SetFramerateLimit(60);

    while (App.IsOpened())
    {
        sf::Event   event;

        while (App.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed || (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape))
            {
                App.Close();
            }

            Gui.InjectEvent(event);
        }


        App.Clear(sf::Color(123, 0, 0));

        Gui.Display();

        App.Display();
    }

    return 0;
}
