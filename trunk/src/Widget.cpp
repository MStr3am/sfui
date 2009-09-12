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
        Widget*     Widget::mHoveredWidget = 0;

        Widget::Widget(Vector2f pos, Vector2f size)
            :   Drawable(pos),
                mSize(size),
                mEnabled(true),
                mVisible(true),
                mFocusable(true),
                mDefaultStyle("BI_Widget"),
                mAlign(Align::NONE),
                mAlignOffset(0.f, 0.f)
        {
            mParent = 0;
        }

        Widget::~Widget()
        {

        }

        void    Widget::SetDefaultStyle(const std::string& style)
        {
            mDefaultStyle = style;
        }

        const std::string&  Widget::GetDefaultStyle() const
        {
            return mDefaultStyle;
        }

        void    Widget::LoadStyle(const std::string& style)
        {
            ResourceManager* rm = ResourceManager::Get();

            StyleProperties& properties = rm->GetStyle(style);

            SetX(rm->GetValue(properties["x"], GetPosition().x));
            SetY(rm->GetValue(properties["y"], GetPosition().y));

            mAlignOffset.x = rm->GetValue(properties["x"], mAlignOffset.x);
            mAlignOffset.y = rm->GetValue(properties["y"], mAlignOffset.y);

            SetWidth(rm->GetValue(properties["width"], GetWidth()));
            SetHeight(rm->GetValue(properties["height"], GetHeight()));

            // Detect alignement
            if (properties["align"] != "")
            {
                std::string strA = properties["align"];

                if (strA == "top_left")
                    mAlign = Align::TOP_LEFT;
                else if (strA == "top_center")
                    mAlign = Align::TOP_CENTER;
                else if (strA == "top_right")
                    mAlign = Align::TOP_RIGHT;
                else if (strA == "left")
                    mAlign = Align::LEFT;
                else if (strA == "center")
                    mAlign = Align::CENTER;
                else if (strA == "right")
                    mAlign = Align::RIGHT;
                else if (strA == "bottom_left")
                    mAlign = Align::BOTTOM_LEFT;
                else if (strA == "bottom_center")
                    mAlign = Align::BOTTOM_CENTER;
                else if (strA == "bottom_right")
                    mAlign = Align::BOTTOM_RIGHT;
                else
                    mAlign = Align::NONE;
            }

            SetColor(rm->GetColorValue(properties["color"], GetColor()));

            SetEnabled(rm->GetValue(properties["enabled"], IsEnabled()));
            SetVisible(rm->GetValue(properties["visible"], IsVisible()));
            SetFocusable(rm->GetValue(properties["focusable"], IsFocusable()));

            UpdatePosition();
        }

        void    Widget::SetColor(const Color& color)
        {
            Drawable::SetColor(color);
            OnChange(Widget::COLOR);
        }

        void    Widget::SetSize(const Vector2f& size)
        {
            mSize.x = size.x;
            mSize.y = size.y;
            OnChange(Widget::SIZE);
        }

        void    Widget::SetSize(float width, float height)
        {
            SetSize(Vector2f(width, height));
        }

        void    Widget::SetWidth(float width)
        {
            mSize.x = width;
            OnChange(Widget::SIZE);
        }

        void    Widget::SetHeight(float height)
        {
            mSize.y = height;
            OnChange(Widget::SIZE);
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

        void        Widget::SetAlignment(Align::Alignment align)
        {
            mAlign = align;
            OnChange(Widget::ALIGNMENT);
        }

        Align::Alignment   Widget::GetAlignment() const
        {
            return mAlign;
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

        bool    Widget::IsHovered() const
        {
            return Widget::mHoveredWidget == this;
        }

        void    Widget::GiveFocusTo(Widget* widget)
        {
            if (!HasFocus())
                return;
            Widget::mFocusedWidget = widget;
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

        void    Widget::UpdatePosition()
        {
            if (!mParent || mAlign == Align::NONE)
              return;

            switch (mAlign)
            {
                case Align::TOP_LEFT :
                    SetPosition(0, 0);
                break;

                case Align::TOP_CENTER :
                    SetPosition((mParent->GetWidth() - GetWidth()) / 2, 0);
                break;

                case Align::TOP_RIGHT :
                    SetPosition(mParent->GetWidth() - GetWidth(), 0);
                break;

                case Align::LEFT :
                    SetPosition(0, (mParent->GetHeight() - GetHeight()) / 2);
                break;

                case Align::CENTER :
                    SetPosition((mParent->GetWidth() - GetWidth()) / 2, (mParent->GetHeight() - GetHeight()) / 2);
                break;

                case Align::RIGHT :
                    SetPosition(mParent->GetWidth() - GetWidth(), (mParent->GetHeight() - GetHeight()) / 2);
                break;

                case Align::BOTTOM_LEFT :
                    SetPosition(0, mParent->GetHeight() - GetHeight());
                break;

                case Align::BOTTOM_CENTER :
                    SetPosition((mParent->GetWidth() - GetWidth()) / 2, mParent->GetHeight() - GetHeight());
                break;

                case Align::BOTTOM_RIGHT :
                    SetPosition(mParent->GetWidth() - GetWidth(), mParent->GetHeight() - GetHeight());
                break;

                default :
                break;

            };

            Move(mAlignOffset);
        }

        void    Widget::Add(Widget* widget)
        {
            if (Find(widget) != mChildren.end())
                return;

            mChildren.push_back(widget);
            widget->mParent = this;
            widget->UpdatePosition();
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
        }
    }
}
