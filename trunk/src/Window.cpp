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

#include "Window.hpp"
#include <iostream>

namespace sf
{
    namespace ui
    {
        Window::Window(const Unicode::Text& title)
            :   MovableWidget(),
                mTitle(title)
        {
            mTitle.SetFocusable(false);
            Add(&mTitle);
        }

        void    Window::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mTitle.SetX((GetWidth() - mTitle.GetWidth()) / 2);
            }
        }

    }

}
