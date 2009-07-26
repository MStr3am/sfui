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

#include "MouseListener.hpp"

namespace sf
{
    namespace ui
    {
        void    MouseListener::OnMouseEvent(const Event& event)
        {
            if (event.Type == Event::MouseButtonPressed)
                OnMousePressed(event.MouseButton);
            else if (event.Type == Event::MouseButtonReleased)
                OnMouseReleased(event.MouseButton);
            else if (event.Type == Event::MouseEntered)
                OnMouseEntered(event.MouseMove);
            else if (event.Type == Event::MouseLeft)
                OnMouseLeft(event.MouseMove);
            else if (event.Type == Event::MouseMoved)
                OnMouseMoved(event.MouseMove);
        }
    }
}
