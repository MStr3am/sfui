#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

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
#include "ImageButton.hpp"

namespace sf
{
    namespace ui
    {
        class CheckBox : public Widget, public MouseListener
        {
            public :
                CheckBox(const Unicode::Text& caption);

                void                    SetChecked(bool checked = true);
                bool                    IsChecked() const;

                void                    SetText(const Unicode::Text& caption);
                const Unicode::Text&    GetText() const;

                void                    SetFont(const Font& font);
                const Font&             GetFont() const;

                void                    SetTextColor(const Color& color);
                const Color&            GetTextColor() const;

                virtual void            LoadStyle(const std::string& nameStyle);

            protected :
                // Inherited from MouseListener
                virtual void            OnMousePressed(const Event::MouseButtonEvent& mouse);

                // Inherited from Widget
                virtual void            Render(RenderTarget& target) const;

            private :
                bool                    mChecked;
                ImageButton             mCheckButton;
                Label                   mCaption;

        };

    }

}

#endif // CHECKBOX_HPP_INCLUDED
