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
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderQueue.hpp>

#include <SFUI/Widget.hpp>
#include <SFUI/MouseListener.hpp>
#include <SFUI/KeyListener.hpp>

#include <algorithm>

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
                mAlignOffset(0.f, 0.f),
                mBorderColor(Color(0,0,0,0)),
                mUseScissor(false)
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

            if (properties["from"] != "")
                LoadStyle(properties["from"]);

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
            SetBorderColor(rm->GetColorValue(properties["borderColor"], GetBorderColor()));

            SetEnabled(rm->GetValue(properties["enabled"], IsEnabled()));
            SetVisible(rm->GetValue(properties["visible"], IsVisible()));
            SetFocusable(rm->GetValue(properties["focusable"], IsFocusable()));

            UpdatePosition();
        }

        void    Widget::SetBorderColor(const Color& borderColor)
        {
            mBorderColor = borderColor;
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

        const Color&        Widget::GetBorderColor() const
        {
            return mBorderColor;
        }

        const Vector2f&     Widget::GetSize() const
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

        void        Widget::SetAlignment(Align::Alignment align, const Vector2f& alignOffset)
        {
            mAlign = align;
            mAlignOffset = alignOffset;
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

        Widget* Widget::GetBrotherAt(Widget::ZIndex op)
        {
            if (!mParent)
                return 0;

            Widgets& container = mParent->mChildren;
            Widget* brother = 0;
            size_t i = 0;

            for (size_t size = container.size(); i < size; ++i)
            {
                if (container.at(i) == this)
                    break;
            }

            if (op == Widget::ALL_BELOW)
            {
                brother = container.front();
            }
            else if (op == Widget::ALL_ABOVE)
            {
                brother = container.back();
            }
            else if (op == Widget::UP && i < container.size() - 1)
            {
                brother = container.at(i + 1);
            }
            else if (op == Widget::DOWN && i > 0)
            {
                brother = container.at(i - 1);
            }

            return brother;
        }

        void    Widget::ChangeZIndex(Widget::ZIndex op)
        {
            if (!mParent)
                return;

            Widgets& container = mParent->mChildren;
            size_t i = 0;

            for (size_t size = container.size(); i < size; ++i)
            {
                if (container.at(i) == this)
                    break;
            }

            if (op == ALL_ABOVE)
            {
                container.erase(container.begin() + i);
                container.push_back(this);
            }
            else if (op == ALL_BELOW)
            {
                container.erase(container.begin() + i);
                container.insert(container.begin(), this);
            }
            else if (op == DOWN && i > 0)
            {
                std::swap(container[i], container[i - 1]);
            }
            else if (op == UP && i < container.size() - 1)
            {
                std::swap(container[i], container[i + 1]);
            }

        }

        void    Widget::Add(Widget* widget)
        {
            if (Find(widget) != mChildren.end())
                return;

            mChildren.push_back(widget);
            widget->mParent = this;
            widget->UpdatePosition();
            widget->OnChange(Widget::PARENT);
        }

        void    Widget::Remove(Widget* widget)
        {
            Widgets::iterator   it = Find(widget);

            if (it == mChildren.end())
                return;

            mChildren.erase(it);
            widget->mParent = 0;
            widget->OnChange(Widget::PARENT);
        }

        void    Widget::AddMouseListener(MouseListener* mouseListener)
        {
            mMouseListeners.push_back(mouseListener);
        }

        void    Widget::RemoveMouseListener(MouseListener* mouseListener)
        {
            for (MouseListeners::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); ++it)
            {
                if (*it == mouseListener)
                {
                    mMouseListeners.erase(it);
                    break;
                }
            }
        }

        void    Widget::AddKeyListener(KeyListener* keyListener)
        {
            mKeyListeners.push_back(keyListener);
        }

        void    Widget::RemoveKeyListener(KeyListener* keyListener)
        {
            for (KeyListeners::iterator it = mKeyListeners.begin(); it != mKeyListeners.end(); ++it)
            {
                if (*it == keyListener)
                {
                    mKeyListeners.erase(it);
                    break;
                }
            }
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

        void    Widget::RenderChildren(RenderTarget& target, RenderQueue& queue) const
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

        void    Widget::OnChange(Widget::Property property)
        {
            if (property == SIZE)
            {
                for (Widgets::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
                {
                    (*it)->UpdatePosition();
                }
            }
        }

        void    Widget::UseScissor(bool useScissor)
        {
            mUseScissor = useScissor;
        }

        void    Widget::OnPaint(RenderTarget& target, RenderQueue& queue) const
        {
            queue.SetColor(GetColor());
            target.Draw(Shape::Rectangle(0, 0, mSize.x, mSize.y, GetColor(), 1.f, GetBorderColor()));
        }

        void    Widget::Render(RenderTarget& target, RenderQueue& queue) const
        {
            OnPaint(target, queue);

            if (mUseScissor)
            {
                Area& area = ResourceManager::Get()->WidgetArea;
                area.PushArea(GetRect(true));
                const FloatRect& top = area.GetTopArea();

                target.Flush();

                RenderChildren(target, queue);

                queue.SetScissor(true, Vector2f(top.Left, target.GetHeight() - top.Bottom), Vector2f(top.GetSize().x, top.GetSize().y));
                target.Flush();
                area.PopArea();
            }
            else
            {
                queue.SetScissor(false);
                RenderChildren(target, queue);
            }
        }
    }
}
