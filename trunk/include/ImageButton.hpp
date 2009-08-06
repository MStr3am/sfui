#ifndef IMAGEBUTTON_HPP_INCLUDED
#define IMAGEBUTTON_HPP_INCLUDED

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

#include "Button.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
    namespace ui
    {
        class ImageButton : public Button
        {
            public :
                ImageButton(const Image& imgReleased, const Image& imgHover, const Image& imgPressed);

            protected :

                // Inherited from Button
                virtual void    OnPressed();
                virtual void    OnReleased();

                // Inherited from MouseListener
                virtual void    OnMouseEntered(const Event::MouseMoveEvent& mouse);
                virtual void    OnMouseLeft(const Event::MouseMoveEvent& mouse);

                // Inherited from Widget
                virtual void    OnPaint(RenderTarget& target) const;
                virtual void    OnChange(Widget::Property property);

            private :
                Image           mImages[3];
                Sprite          mCurrentSprite;



        };
    }
}


#endif // IMAGEBUTTON_HPP_INCLUDED
