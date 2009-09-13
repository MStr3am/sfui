#ifndef ICON_HPP_INCLUDED
#define ICON_HPP_INCLUDED

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

#include "Widget.hpp"
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
    namespace ui
    {
        class Icon : public Widget
        {
            public :
                Icon();
                Icon(const Sprite& sprite);
                Icon(const std::string& filename);

                void            SetImage(const Image& image, bool resize = true);
                const Image*    GetImage() const;

                virtual void    LoadStyle(const std::string& nameStyle);

            protected :
                virtual void    OnPaint(RenderTarget& target) const;
                virtual void    OnChange(Widget::Property property);

            private :
                Sprite          mSprite;
        };
    }
}


#endif // ICON_HPP_INCLUDED
