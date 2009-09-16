#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

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

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "ResourceManager.hpp"

namespace sf
{
    namespace ui
    {
        class Widget;
        class GuiRenderer;
        class MouseListener;
        class KeyListener;

        typedef std::vector<Widget*> Widgets;
        typedef std::vector<MouseListener*> MouseListeners;
        typedef std::vector<KeyListener*> KeyListeners;

        namespace Align
        {
            typedef enum
            {
                NONE = -1,

                TOP_LEFT = 0,
                TOP_CENTER,
                TOP_RIGHT,

                LEFT,
                RIGHT,
                CENTER,

                BOTTOM_LEFT,
                BOTTOM_CENTER,
                BOTTOM_RIGHT

            }   Alignment;
        }

        class Widget : public Drawable
        {
            friend class GuiRenderer;

            public:

                typedef enum
                {
                    NONE = 0,

                    COLOR,
                    SIZE,
                    ENABLE,
                    VISIBLE,
                    FOCUSABLE,
                    ALIGNMENT,
                    PARENT

                }   Property;

                typedef enum
                {
                    ALL_ABOVE,
                    ALL_BELOW,
                    UP,
                    DOWN
                }   ZIndex;

                Widget(Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(20, 20));
                ~Widget();

                void                SetDefaultStyle(const std::string& defaultStyle);
                const std::string&  GetDefaultStyle() const;

                virtual void        LoadStyle(const std::string& style = "");

                void                SetColor(const Color& color);

                void                SetSize(const Vector2f& size);
                void                SetSize(float width, float height);
                void                SetWidth(float width);
                void                SetHeight(float height);

                const Vector2f&     GetSize() const;
                float               GetWidth() const;
                float               GetHeight() const;

                void                SetAlignment(Align::Alignment align);
                Align::Alignment    GetAlignment() const;

                FloatRect           GetRect(bool absolute) const;

                Vector2f            GetAbsolutePosition() const;

                void                SetEnabled(bool enable = true);
                void                SetVisible(bool visible = true);
                void                SetFocusable(bool focusable = true);

                bool                IsEnabled() const;
                bool                IsVisible() const;
                bool                IsFocusable() const;
                bool                IsHovered() const;

                void                GiveFocusTo(Widget* widget);
                bool                HasFocus() const;

                void                Add(Widget* widget);
                void                Remove(Widget* widget);

                const Widgets&      GetChildren() const;

                Widget*             GetParent() const;

                void                AddMouseListener(MouseListener* mouseListener);
                void                RemoveMouseListener(MouseListener* MouseListener);

                void                AddKeyListener(KeyListener* keyListener);
                void                RemoveKeyListener(KeyListener* KeyListener);

                void                UpdatePosition();

                void                ChangeZIndex(Widget::ZIndex op);
                Widget*             GetBrotherAt(Widget::ZIndex op);

            protected:
                virtual void        Render(RenderTarget& target) const;
                virtual void        OnPaint(RenderTarget& target) const;
                virtual void        OnChange(Widget::Property property);

            private:
                void                DistributeEvent(const Event& event);
                void                RenderChildren(RenderTarget& target) const;

                Widgets::iterator   Find(const Widget* widget);

                Vector2f            mSize;
                Widgets             mChildren;
                Widget*             mParent;

                bool                mEnabled;
                bool                mVisible;
                bool                mFocusable;

                MouseListeners      mMouseListeners;
                KeyListeners        mKeyListeners;

                static Widget*      mFocusedWidget;
                static Widget*      mHoveredWidget;

                std::string         mDefaultStyle;

                Align::Alignment    mAlign;
                Vector2f            mAlignOffset;
        };

    }


}

#endif // WIDGET_HPP_INCLUDED
