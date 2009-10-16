/*
    Copyright (c) 2009, Robin RUAUX
    All rights reserved.
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the University of California, Berkeley nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <SFUI/MovablePolicy.hpp>

namespace sf
{
    namespace ui
    {

        MovablePolicy::MovablePolicy(Widget& widget)
            :   Policy(widget, "MovablePolicy"),
                mMovableX(true),
                mMovableY(true),
                mBlocked(false),
                mDragged(false),
                mDragOffset(0.f, 0.f),
                mNeedUpdate(false)
        {

        }

        void    MovablePolicy::SetMovable(bool movable)
        {
            mMovableX = mMovableY = movable;
        }

        void    MovablePolicy::SetMovableX(bool movable)
        {
            mMovableX = movable;
        }

        void    MovablePolicy::SetMovableY(bool movable)
        {
            mMovableY = movable;
        }

        void    MovablePolicy::SetBlocked(bool blocked)
        {
            mBlocked = blocked;
        }

        bool    MovablePolicy::IsMovable() const
        {
            return (mMovableX || mMovableY);
        }

        bool    MovablePolicy::IsMovableX() const
        {
            return mMovableX;
        }

        bool    MovablePolicy::IsMovableY() const
        {
            return mMovableY;
        }

        bool    MovablePolicy::IsBlocked() const
        {
            return mBlocked;
        }

        void    MovablePolicy::LoadStyle(const std::string& styleName)
        {
            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(styleName);

            SetMovable(rm->GetValue(properties["movable"], IsMovable()));
            SetMovableX(rm->GetValue(properties["movableX"], IsMovableX()));
            SetMovableY(rm->GetValue(properties["movableY"], IsMovableY()));
            SetBlocked(rm->GetValue(properties["blocked"], IsBlocked()));
        }

        void    MovablePolicy::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (!IsMovable())
                return;

            mDragged = true;
            mNeedUpdate = true;

            mWidget.ChangeZIndex(Widget::ALL_ABOVE);
        }

        void    MovablePolicy::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            mDragged = false;
        }

        void    MovablePolicy::OnMouseMoved(const Event::MouseMoveEvent& mouse)
        {
            if (mDragged && IsMovable())
            {
                const Vector2f& mousePos = Vector2f(mouse.X, mouse.Y);
                const Vector2f& absPos = mWidget.GetAbsolutePosition();

                if (mNeedUpdate)
                {
                    mNeedUpdate = false;
                    mDragOffset = mousePos - absPos;
                }

                Vector2f newPos = mousePos - mDragOffset;
                Widget* parent = mWidget.GetParent();

                if (parent && mBlocked)
                {
                    const Vector2f& limitPos = absPos - mWidget.GetPosition();

                    if (newPos.x < limitPos.x)
                        newPos.x = limitPos.x;
                    else if (newPos.x + mWidget.GetWidth() > limitPos.x + parent->GetWidth())
                        newPos.x = limitPos.x + parent->GetWidth() - mWidget.GetWidth();

                    if (newPos.y < limitPos.y)
                        newPos.y = limitPos.y;
                    else if (newPos.y + mWidget.GetHeight() > limitPos.y + parent->GetHeight())
                        newPos.y = limitPos.y + parent->GetHeight() - mWidget.GetHeight();
                }

                if (!mMovableX)
                    newPos.x = absPos.x;

                if (!mMovableY)
                    newPos.y = absPos.y;

                mWidget.Move(newPos - absPos);
                mWidget.SetAlignment(Align::NONE);
            }
        }
    }
}
