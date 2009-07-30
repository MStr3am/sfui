#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

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

#include "Label.hpp"
#include "MouseListener.hpp"

namespace sf
{
    namespace ui
    {
        class Button : public Widget, public MouseListener
        {
            public :
                Button();

                void            SetPressed(bool pressed = true);
                bool            IsPressed() const;

            protected :

                virtual void    OnPressed() {};
                virtual void    OnReleased() {};

                // Inherited from MouseListener.
                virtual void    OnMousePressed(const Event::MouseButtonEvent& button);
                virtual void    OnMouseReleased(const Event::MouseButtonEvent& button);
                virtual void    OnMouseLeft(const Event::MouseMoveEvent& mouse);

            private :
                bool            mPressed;

        };
    }

}

#endif // BUTTON_HPP_INCLUDED
