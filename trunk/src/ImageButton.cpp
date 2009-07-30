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

namespace sf
{
    namespace ui
    {
        ImageButton::ImageButton(const Image& imgPressed, const Image& imgReleased)
            :   Button(),
                mCurrentSprite(imgReleased)
        {
            mImages[0] = imgPressed;
            mImages[1] = imgReleased;

            SetSize(mCurrentSprite.GetSize().x, mCurrentSprite.GetSize().y);
        }


        void    ImageButton::OnPressed()
        {
            mCurrentSprite.SetImage(mImages[0]);
        }

        void    ImageButton::OnReleased()
        {
            mCurrentSprite.SetImage(mImages[1]);
        }

        void    ImageButton::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mCurrentSprite.Resize(GetWidth(), GetHeight());
            }
        }

        void    ImageButton::OnPaint(RenderTarget& target) const
        {
            target.Draw(mCurrentSprite);
        }



    }
}
