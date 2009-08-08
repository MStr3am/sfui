#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

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
#include <SFML/Graphics/String.hpp>

namespace sf
{
    namespace ui
    {
        class Label : public Widget
        {
            public :
                Label(const Unicode::Text& caption, float textSize = 30.f);

                void                    SetText(const Unicode::Text& caption);
                const Unicode::Text&    GetText() const;

                void                    SetFont(const Font& font);
                const Font&             GetFont() const;

                void                    SetTextSize(float size);
                float                   GetTextSize() const;

                void                    SetTextColor(const Color& color);
                const Color&            GetTextColor() const;

                const String&           GetString() const;

            protected :

                // Inherited from Widget
                virtual void            Render(RenderTarget& target) const;
                virtual void            LoadTemplate(const std::string& nameTpl);


            private :
                String                  mCaption;

        };

    }

}

#endif // LABEL_HPP_INCLUDED
