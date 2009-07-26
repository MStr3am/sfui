#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

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

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

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

                    NB_STATES
                } Property;


                Widget(Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(20, 20));
                ~Widget();

                void                SetColor(const Color& color);

                void                SetSize(const Vector2f& size);
                void                SetSize(float width, float height);
                void                SetWidth(float width);
                void                SetHeight(float height);

                const Vector2f&     GetSize() const;
                float               GetWidth() const;
                float               GetHeight() const;

                FloatRect           GetRect(bool absolute) const;

                Vector2f            GetAbsolutePosition() const;

                void                SetEnabled(bool enable);
                void                SetVisible(bool visible);
                void                SetFocusable(bool focusable);

                bool                IsEnabled() const;
                bool                IsVisible() const;
                bool                IsFocusable() const;

                bool                HasFocus() const;

                void                Add(Widget* widget);
                void                Remove(Widget* widget);

                const Widgets&      GetChildren() const;

                Widget*             GetParent() const;

                void                AddMouseListener(MouseListener* mouseListener);
                void                AddKeyListener(KeyListener* keyListener);

            protected:
                virtual void        Render(RenderTarget& target) const;
                virtual void        OnPaint(RenderTarget& target) const;
                virtual void        OnChange(Property property) {};

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

        };

    }


}

#endif // WIDGET_HPP_INCLUDED
