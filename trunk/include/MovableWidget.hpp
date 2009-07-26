#ifndef MOVABLEWIDGET_HPP_INCLUDED
#define MOVABLEWIDGET_HPP_INCLUDED

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
#include "MouseListener.hpp"

namespace sf
{
    namespace ui
    {
        class MovableWidget : public Widget, public MouseListener
        {
            public :

                MovableWidget();

                void            SetMovable(bool movable = true);
                void            SetBlocked(bool blocked = true);

                bool            IsMovable() const;
                bool            IsBlocked() const;

            protected :
                virtual void    OnMousePressed(const Event::MouseButtonEvent& button);
                virtual void    OnMouseReleased(const Event::MouseButtonEvent& button);
                virtual void    OnMouseMoved(const Event::MouseMoveEvent& mouse);

            private :
                bool            mMovable;
                bool            mBlocked;

                bool            mDragged;
                Vector2f        mDragOffset;
                bool            mNeedUpdate;

        };

    }

}

#endif // MOVABLEWIDGET_HPP_INCLUDED
