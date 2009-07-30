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
        Button::Button()
            :   Widget(),
                mPressed(false)
        {
            AddMouseListener(this);
        }

        void    Button::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (!mPressed)
            {
                mPressed = true;
                OnPressed();
            }
        }

        void    Button::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            if (mPressed)
            {
                mPressed = false;
                OnReleased();
            }
        }

        void    Button::OnMouseLeft(const Event::MouseMoveEvent& mouse)
        {
            if (mPressed)
            {
                mPressed = false;
                OnReleased();
            }
        }

        void    Button::SetPressed(bool pressed)
        {
            mPressed = pressed;
        }

        bool    Button::IsPressed() const
        {
            return mPressed;
        }


    }

}
