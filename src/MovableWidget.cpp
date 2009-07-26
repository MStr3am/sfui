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

#include "MovableWidget.hpp"
#include <iostream>

namespace sf
{
    namespace ui
    {

        MovableWidget::MovableWidget()
            :   Widget(),
                mMovable(true),
                mDragged(false),
                mDragOffset(0.f, 0.f),
                mNeedUpdate(false)
        {
            AddMouseListener(this);
        }

        void    MovableWidget::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (!mMovable)
                return;

            mDragged = true;
            mNeedUpdate = true;
        }

        void    MovableWidget::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            mDragged = false;
        }

        void    MovableWidget::OnMouseMoved(const Event::MouseMoveEvent& mouse)
        {
            if (mDragged && mMovable)
            {
                const Vector2f& mousePos = Vector2f(mouse.X, mouse.Y);
                const Vector2f& absPos = GetAbsolutePosition();

                if (mNeedUpdate)
                {
                    mNeedUpdate = false;
                    mDragOffset = mousePos - absPos;
                }

                Vector2f newPos = mousePos - mDragOffset;
                Widget* parent = GetParent();

                if (parent)
                {
                    const Vector2f& limitPos = absPos - GetPosition();

                    if (newPos.x < limitPos.x)
                        newPos.x = limitPos.x;
                    else if (newPos.x + GetWidth() > limitPos.x + parent->GetWidth())
                        newPos.x = limitPos.x + parent->GetWidth() - GetWidth();

                    if (newPos.y < limitPos.y)
                        newPos.y = limitPos.y;
                    else if (newPos.y + GetHeight() > limitPos.y + parent->GetHeight())
                        newPos.y = limitPos.y + parent->GetHeight() - GetHeight();
                }

                Move(newPos - absPos);
            }
        }
    }
}
