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

#include "TextButton.hpp"

namespace sf
{
    namespace ui
    {
        TextButton::TextButton(const Unicode::Text& caption, float size)
            :   Button(),
                mCaption(caption, size)
        {
            mCaption.SetFocusable(false);
            Add(&mCaption);

            SetSize(mCaption.GetSize() + Vector2f(18, 10));
            SetColor(Color(123, 123, 123));
        }

        void    TextButton::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mCaption.SetX((GetWidth() - mCaption.GetSize().x) / 2);
                mCaption.SetY((GetHeight() - mCaption.GetSize().y) / 2);
            }
        }

        void    TextButton::SetTextColor(const Color& color)
        {
            mCaption.SetColor(color);
        }

        const Color&    TextButton::GetTextColor() const
        {
            return mCaption.GetColor();
        }

        void    TextButton::SetTextSize(float size)
        {
            mCaption.SetTextSize(size);
        }

        float   TextButton::GetTextSize() const
        {
            return mCaption.GetTextSize();
        }

        void    TextButton::OnPressed()
        {
            mCaption.Move(2.f, 2.f);
        }

        void    TextButton::OnReleased()
        {
            mCaption.Move(-2.f, -2.f);
        }

    }
}
