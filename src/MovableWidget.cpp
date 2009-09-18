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

#include <SFUI/MovableWidget.hpp>

namespace sf
{
    namespace ui
    {

        MovableWidget::MovableWidget()
            :   Widget(),
                mMovable(true),
                mBlocked(false),
                mDragged(false),
                mDragOffset(0.f, 0.f),
                mNeedUpdate(false)
        {
            SetDefaultStyle("BI_MovableWidget");
            LoadStyle(GetDefaultStyle());
            AddMouseListener(this);
        }

        void    MovableWidget::SetMovable(bool movable)
        {
            mMovable = movable;
        }

        void    MovableWidget::SetBlocked(bool blocked)
        {
            mBlocked = blocked;
        }

        bool    MovableWidget::IsMovable() const
        {
            return mMovable;
        }

        bool    MovableWidget::IsBlocked() const
        {
            return mBlocked;
        }


        void    MovableWidget::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            SetMovable(rm->GetValue(properties["movable"], IsMovable()));
            SetBlocked(rm->GetValue(properties["blocked"], IsBlocked()));
        }

        void    MovableWidget::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (!mMovable)
                return;

            mDragged = true;
            mNeedUpdate = true;

            ChangeZIndex(Widget::ALL_ABOVE);
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

                if (parent && mBlocked)
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
                SetAlignment(Align::NONE);
            }
        }
    }
}
