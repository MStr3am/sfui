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

#include "ImageButton.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace sf
{
    namespace ui
    {
        ImageButton::ImageButton()
            :   Button(),
                mCurrentSprite()
        {
            SetDefaultStyle("BI_ImageButton");
            LoadStyle(GetDefaultStyle());
        }

        void    ImageButton::OnPressed()
        {
            LoadStyle(GetDefaultStyle() + "_Pressed");
        }

        void    ImageButton::OnReleased()
        {
            LoadStyle(GetDefaultStyle() + "_Hovered");
        }

        void    ImageButton::OnMouseEntered(const Event::MouseMoveEvent& mouse)
        {
            LoadStyle(GetDefaultStyle() + "_Hovered");
        }

        void    ImageButton::OnMouseLeft(const Event::MouseMoveEvent& mouse)
        {
            Button::OnMouseLeft(mouse);
            LoadStyle(GetDefaultStyle());
        }

        void    ImageButton::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            if (properties["image"] != "")
            {
                mCurrentSprite = rm->GetImage(properties["image"]);
                mCurrentSprite.Resize(GetWidth(), GetHeight());
            }
        }

        void    ImageButton::OnPaint(RenderTarget& target) const
        {
            Widget::OnPaint(target);
            target.Draw(mCurrentSprite);
        }

    }
}
