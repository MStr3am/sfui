#ifndef MOUSELISTENER_HPP_INCLUDED
#define MOUSELISTENER_HPP_INCLUDED

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
        class MouseListener
        {
            public :

                void            OnMouseEvent(const Event& event);

            protected :

                virtual void    OnMousePressed(const Event& event) {};
                virtual void    OnMouseReleased(const Event& event) {};
                virtual void    OnMouseEntered(const Event& event) {};
                virtual void    OnMouseLeft(const Event& event) {};
                virtual void    OnMouseMoved(const Event& event) {};

        };
    }
}

#endif // MOUSELISTENER_HPP_INCLUDED
