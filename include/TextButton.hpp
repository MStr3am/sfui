#ifndef TEXTBUTTON_HPP_INCLUDED
#define TEXTBUTTON_HPP_INCLUDED

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

namespace sf
{
    namespace ui
    {
        class TextButton : public Button
        {
            public :
                TextButton(const Unicode::Text& caption, float textSize = 15.f);

                void            SetTextColor(const Color& color);
                const Color&    GetTextColor() const;

                void            SetTextSize(float size);
                float           GetTextSize() const;

            protected :
                // Inherited from Widget
                virtual void    OnChange(Widget::Property property);
                virtual void    LoadTemplate(const std::string& nameTpl);
                virtual void    Render(RenderTarget& target) const;

                // Inherited from Button
                virtual void    OnPressed();
                virtual void    OnReleased();

            private :
                Label           mCaption;



        };

    }
}

#endif // TEXTBUTTON_HPP_INCLUDED
