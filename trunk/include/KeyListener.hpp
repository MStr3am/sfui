#ifndef KEYLISTENER_HPP_INCLUDED
#define KEYLISTENER_HPP_INCLUDED

/*
    This file is part of SFUI (by Robin RUAUX).

    SFUI is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SFUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SFUI.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <SFML/Window/Event.hpp>

namespace sf
{
    namespace ui
    {
        class KeyListener
        {
            public :

                void            OnKeyEvent(const Event& event);

            protected :

                virtual void    OnKeyPressed(const Event::KeyEvent& key) {};
                virtual void    OnKeyReleased(const Event::KeyEvent& key) {};

                virtual void    OnTextEntered(const Event::TextEvent& text) {};

        };

    }


}

#endif // KEYLISTENER_HPP_INCLUDED
