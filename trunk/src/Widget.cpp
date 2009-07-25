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
#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "MouseListener.hpp"
#include "KeyListener.hpp"

#include <iostream>

namespace sf
{
    namespace ui
    {
        Widget*     Widget::mFocusedWidget = 0;

        Widget::Widget(Vector2f pos, Vector2f size)
            :   Drawable(pos),
                mSize(size),
                mEnabled(true),
                mVisible(true),
                mFocusable(true)
        {
            mParent = 0;
        }

        Widget::~Widget()
        {

        }

        void    Widget::SetColor(const Color& color)
        {
            Drawable::SetColor(color);
            OnChange(Widget::COLOR);
        }

        void    Widget::SetSize(const Vector2f& size)
        {
            mSize = size;
            OnChange(Widget::SIZE);
        }

        void    Widget::SetSize(float width, float height)
        {
            SetSize(Vector2f(width, height));
        }

        void    Widget::SetWidth(float width)
        {
            SetSize(Vector2f(width, GetHeight()));
        }

        void    Widget::SetHeight(float height)
        {
            SetSize(Vector2f(GetWidth(), height));
        }

        const Vector2f&    Widget::GetSize() const
        {
            return mSize;
        }

        float   Widget::GetWidth() const
        {
            return mSize.x;
        }

        float   Widget::GetHeight() const
        {
            return mSize.y;
        }

        FloatRect   Widget::GetRect(bool absolute) const
        {
            const Vector2f& pos = (absolute) ? GetAbsolutePosition() : GetPosition();

            return FloatRect(pos.x, pos.y, pos.x + GetWidth(), pos.y + GetHeight());
        }

        Vector2f     Widget::GetAbsolutePosition() const
        {
            Vector2f absPos(0.f, 0.f);
            const Widget* currentWidget = this;

            while (currentWidget)
            {
                absPos += currentWidget->GetPosition();
                currentWidget = currentWidget->GetParent();
            }

            return absPos;
        }

        void    Widget::SetEnabled(bool enable)
        {
            mEnabled = enable;
            OnChange(Widget::ENABLE);
        }

        void    Widget::SetVisible(bool visible)
        {
            mVisible = visible;
            OnChange(Widget::VISIBLE);
        }

        void    Widget::SetFocusable(bool focusable)
        {
            mFocusable = focusable;
            OnChange(Widget::FOCUSABLE);
        }

        bool    Widget::IsEnabled() const
        {
            return mEnabled;
        }

        bool    Widget::IsVisible() const
        {
            return mVisible;
        }

        bool    Widget::IsFocusable() const
        {
            return mFocusable;
        }

        bool    Widget::HasFocus() const
        {
            return Widget::mFocusedWidget == this;
        }

        const Widgets& Widget::GetChildren() const
        {
            return mChildren;
        }

        Widget*     Widget::GetParent() const
        {
            return mParent;
        }

        Widgets::iterator    Widget::Find(const Widget *widget)
        {
            for (Widgets::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
            {
                if (*it == widget)
                    return (it);
            }

            return (mChildren.end());
        }

        void    Widget::Add(Widget* widget)
        {
            if (Find(widget) != mChildren.end())
                return;

            mChildren.push_back(widget);
            widget->mParent = this;
        }

        void    Widget::Remove(Widget* widget)
        {
            Widgets::iterator   it = Find(widget);

            if (it == mChildren.end())
                return;

            mChildren.erase(it);
            widget->mParent = 0;
        }

        void    Widget::AddMouseListener(MouseListener* mouseListener)
        {
            mMouseListeners.push_back(mouseListener);
        }

        void    Widget::AddKeyListener(KeyListener* keyListener)
        {
            mKeyListeners.push_back(keyListener);
        }

        void    Widget::DistributeEvent(const Event& event)
        {
            if (!mEnabled)
                return;

            for (MouseListeners::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); ++it)
            {
                (*it)->OnMouseEvent(event);
            }

            for (KeyListeners::iterator it = mKeyListeners.begin(); it != mKeyListeners.end(); ++it)
            {
                (*it)->OnKeyEvent(event);
            }

        }

        void    Widget::RenderChildren(RenderTarget& target) const
        {
            if (!mVisible)
                return;

            for (Widgets::const_iterator it = mChildren.begin(); it != mChildren.end(); ++it)
            {
                Widget* widg = *it;

                if (widg->IsVisible())
                    target.Draw(*widg);
            }

        }

        void    Widget::OnPaint(RenderTarget& target) const
        {
            glDisable(GL_TEXTURE_2D);

            glBegin(GL_QUADS);
                glVertex2f(0,     0);
                glVertex2f(0,     mSize.y);
                glVertex2f(mSize.x, mSize.y);
                glVertex2f(mSize.x, 0);
            glEnd();
        }

        void    Widget::Render(RenderTarget& target) const
        {
            OnPaint(target);
            RenderChildren(target);

            // Reinitialize the scissor
            glScissor(0, 0, target.GetWidth(), target.GetHeight());
        }
    }
}
