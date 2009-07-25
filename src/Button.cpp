/*
    This file is part of ReGen (by Robin RUAUX).

    ReGen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ReGen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ReGen.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Button.hpp"
#include <iostream>

namespace sf
{
        Button::Button(const Unicode::Text& caption, float size)
            :   Widget(),
                mCaption(caption, size),
                mPressed(false)
        {
            mCaption.SetFocusable(false);

            AddMouseListener(this);
            Add(&mCaption);

            SetSize(mCaption.GetSize() + Vector2f(18, 10));
        }

        void    Button::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mCaption.SetX((GetWidth() - mCaption.GetSize().x) / 2);
                mCaption.SetY((GetHeight() - mCaption.GetSize().y) / 2 - 2);
            }
        }

        void    Button::OnMousePressed(const Event& event)
        {
            if (!mPressed)
            {
                mCaption.Move(2.f, 2.f);
                mPressed = true;
            }
        }

        void    Button::OnMouseReleased(const Event& event)
        {
            if (mPressed)
            {
                mCaption.Move(-2.f, -2.f);
                mPressed = false;
            }
        }

        void    Button::OnMouseLeft(const Event& event)
        {
            if (mPressed)
            {
                mCaption.Move(-2.f, -2.f);
                mPressed = false;
            }
        }

        bool    Button::IsPressed() const
        {
            return mPressed;
        }

        void    Button::OnPaint(RenderTarget& target) const
        {
            Widget::OnPaint(target);
        }


}
