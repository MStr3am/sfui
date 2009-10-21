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

/** \file Widget.hpp
 * \brief The main concept in SFUI.
 * \author Robin Ruaux
 */

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <SFUI/ResourceManager.hpp>

namespace sf
{
    namespace ui
    {
        class Widget;
        class GuiRenderer;
        class MouseListener;
        class KeyListener;

        /** \typedef std::vector<KeyListener*> KeyListeners
         *
         * A basic container of KeyListeners.
         */
        typedef std::vector<KeyListener*> KeyListeners;


        /** \typedef std::vector<MouseListener*> MouseListeners
         *
         * A basic container of MouseListeners.
         */
        typedef std::vector<MouseListener*> MouseListeners;


        /** \typedef std::vector<Widget*> Widgets
         *
         * A basic container of widgets.
         */
        typedef std::vector<Widget*> Widgets;


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


        /** \class Widget
         *
         * \brief The main class in SFUI.
         *
         * A widget is a very common class in SFUI, because all other items are based on it.
         */
        class Widget : public Drawable
        {
            friend class GuiRenderer;

            public :

                /** \enum Property
                 *
                 * \brief Enumeration of widget properties.
                 *
                 * These properties are mainly used by OnChange(Widget::Property) method.
                 */
                typedef enum
                {
                    NONE = 0,

                    ALIGNMENT,
                    COLOR,
                    ENABLE,
                    FOCUSABLE,
                    PARENT,
                    SIZE,
                    VISIBLE

                }   Property;


                /** \enum ZIndex
                 *
                 * \brief Enumeration of ZIndex operations.
                 *
                 * These operations are mainly used by ChangeZIndex(Widget::ZIndex) method to change its depth on screen.
                 */
                typedef enum
                {
                    ALL_ABOVE,
                    ALL_BELOW,
                    DOWN,
                    UP
                }   ZIndex;


                /** \brief Constructor
                 *
                 * Constructor of widget class.
                 * \param pos Initial widget position.
                 * \param size Initial widget size.
                 */
                Widget(Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(20, 20));


                /** \brief Destructor
                 *
                 * Destructor of widget class.
                 */
                ~Widget();


                /** \brief Add a new child to the widget.
                 *
                 * When a widget gets a new child, the alignment relation is applied between them.
                 * The child position becomes the alignment shift (offset).
                 * \param widget The widget to be added.
                 */
                void                Add(Widget* widget);


                /** \brief Add a KeyListener to the widget.
                 *
                 * \param keyListener The KeyListener instance to be added.
                 */
                void                AddKeyListener(KeyListener* keyListener);


                /** \brief Add a MouseListener to the widget.
                 *
                 * \param mouseListener The MouseListener instance to be added.
                 */
                void                AddMouseListener(MouseListener* mouseListener);


                /** \brief Change z-index property.
                 *
                 * This method is very useful to change widget depth on screen.
                 *
                 * Use ZIndex::UP or ZIndex::DOWN to shift the widget step by step.
                 *
                 * Use ZIndex::ALL_ABOVE to put it before other brothers.
                 *
                 * Use ZIndex::ALL_BELOW to put it behind other brothers.
                 * \param op The z-index operation.
                 */
                void                ChangeZIndex(Widget::ZIndex op);


                /** \brief Get the absolute position of the widget.
                 *
                 * \return The widget absolute position.
                 */
                Vector2f            GetAbsolutePosition() const;


                /** \brief Get the widget alignment.
                 *
                 * \return The widget alignment.
                 */
                Align::Alignment    GetAlignment() const;


                /** \brief Get the widget border color.
                 *
                 * \return The widget border color.
                 */
                const Color&        GetBorderColor() const;

                /** \brief Get a widget brother with z-index operation.
                 *
                 * You can get a widget brother by selecting it with a z-index operation.
                 *
                 * Use ZIndex::UP or ZIndex::DOWN to select the immediate brother front or behind it.
                 *
                 * Use ZIndex::ALL_ABOVE to select the widget all above others.
                 *
                 * Use ZIndex::ALL_BELOW to select the widget all below others.
                 * \param op The z-index operation.
                 */
                Widget*             GetBrotherAt(Widget::ZIndex op);


                /** \brief Get the widget children.
                 *
                 * \return The widget children (as a std::vector container).
                 */
                const Widgets&      GetChildren() const;


                /** \brief Get the default style value.
                 *
                 * \return The default style value.
                 */
                const std::string&  GetDefaultStyle() const;


                /** \brief Get the widget height.
                 *
                 * \return The widget height.
                 */
                float               GetHeight() const;


                /** \brief Get the widget parent.
                 *
                 * \return The widget parent (0 if not exist).
                 */
                Widget*             GetParent() const;


                /** \brief Get the widget rectangle.
                 *
                 * \param absolute Use absolute or relative position.
                 * \return The widget rectangle.
                 */
                FloatRect           GetRect(bool absolute = true) const;


                /** \brief Get the widget size.
                 *
                 * \return The widget size.
                 */
                const Vector2f&     GetSize() const;


                /** \brief Get the widget width.
                 *
                 * \return The widget width.
                 */
                float               GetWidth() const;


                /** \brief Give the focus to another widget.
                 *
                 * This method allows a widget to give the focus to another one, only if itself already has the focus.
                 * \param widget The new widget to be focused.
                 */
                void                GiveFocusTo(Widget* widget);


                /** \brief Check if the widget is focused.
                 *
                 * \return The widget focused state..
                 */
                bool                HasFocus() const;

                /** \brief Check if the widget is enabled.
                 *
                 * \return The widget enabled property.
                 */
                bool                IsEnabled() const;


                /** \brief Check if the widget is focusable.
                 *
                 * \return The widget focusable property.
                 */
                bool                IsFocusable() const;


                /** \brief Check if the widget is hovered by the mouse.
                 *
                 * \return The widget hovered state.
                 */
                bool                IsHovered() const;


                /** \brief Check if the widget is visible.
                 *
                 * \return The widget visibility.
                 */
                bool                IsVisible() const;


                /** \brief Load a new style for the widget.
                 *
                 * This method is virtual and could be reimplemented by other widgets to load other properties from styles.
                 * \param style The style string value to load.
                 */
                virtual void        LoadStyle(const std::string& style = "");


                /** \brief Remove a child from the widget.
                 *
                 * \param widget To widget to be removed.
                 */
                void                Remove(Widget* widget);


                /** \brief Remove a KeyListener to the widget.
                 *
                 * \param keyListener The MouseListener instance to be removed.
                 */
                void                RemoveKeyListener(KeyListener* keyListener);


                /** \brief Remove a MouseListener instance from the widget.
                 *
                 * \param mouseListener The MouseListener instance to be removed.
                 */
                void                RemoveMouseListener(MouseListener* mouseListener);


                /** \brief Set the widget alignment.
                 *
                 * Alignment is just a relation between a widget and its direct parent.
                 * This method do not update the widget position to its parent. You should use UpdatePosition() for it.
                 * \param align The new widget alignment.
                 * \param alignOffset The alignment offset.
                 */
                void                SetAlignment(Align::Alignment align, const Vector2f& alignOffset = Vector2f(0, 0));


                /** \brief Set the border color of the widget.
                 *
                 * \param borderColor The new widget border color.
                 */
                void                SetBorderColor(const Color& borderColor);


                /** \brief Set the base color of the widget.
                 *
                 * The widget color is by default its background color, but it can be used for other needs.
                 *
                 * This method mask the Drawable::SetColor() in order to send a Property::COLOR signal.
                 * \param color The background color.
                 */
                void                SetColor(const Color& color);


                /** \brief Set the default style used by the widget.
                 *
                 * \param defaultStyle The default style string value.
                 */
                void                SetDefaultStyle(const std::string& defaultStyle);


                /** \brief Set the widget enabled or not
                 *
                 * This method send a Property::ENABLE signal.
                 * \param enable The enabled property.
                 */
                void                SetEnabled(bool enable = true);


                /** \brief Set the widget focusable or not.
                 *
                 * This method send a Property::FOCUSABLE signal.
                 * \param focusable The focusable property.
                 */
                void                SetFocusable(bool focusable = true);


                /** \brief Set the widget height.
                 *
                 * This method send a Property::SIZE signal.
                 * \param height The new widget height.
                 */
                void                SetHeight(float height);


                /** \brief Set the widget size.
                 *
                 * This method send a Property::SIZE signal.
                 * \param size The new widget size (Vector2f).
                 */
                void                SetSize(const Vector2f& size);

                /** \brief Set the widget size.
                 *
                 * This method send a Property::SIZE signal.
                 * \param width The new widget width.
                 * \param height The new widget height.
                 */
                void                SetSize(float width, float height);


                /** \brief Set the widget visibility.
                 *
                 * When a widget is hidden, its children are hidden too.
                 * \param visible The widget visibility.
                 */
                void                SetVisible(bool visible = true);


                /** \brief Set the widget width.
                 *
                 * This method send a Property::SIZE signal.
                 * \param width The new widget width.
                 */
                void                SetWidth(float width);


                /** \brief Update the widget position.
                 *
                 * When this method is called, the widget realign itself with its parent.
                 */
                void                UpdatePosition();

                /** \brief Enable the scissor test to render the widget
                 *
                 * \param useScissor Enable or not the scissor test.
                 */
                void                UseScissor(bool useScissor);


            protected:

                /** \brief Called when a widget property-changed signal has been received. */
                virtual void        OnChange(Widget::Property property);

                /** \brief Called when the widget is drawed on screen. */
                virtual void        OnPaint(RenderTarget& target, RenderQueue& queue) const;

                /** \brief Render the widget to the screen. */
                virtual void        Render(RenderTarget& target, RenderQueue& queue) const;

            private:

                /** \brief Distribute an event to listeners */
                void                DistributeEvent(const Event& event);

                /** \brief Check if the widget is a direct child. */
                Widgets::iterator   Find(const Widget* widget);

                /** \brief Call children render method. */
                void                RenderChildren(RenderTarget& target, RenderQueue& queue) const;

                Align::Alignment    mAlign;

                Vector2f            mAlignOffset;

                Color               mBorderColor;

                Widgets             mChildren;

                std::string         mDefaultStyle;

                bool                mEnabled;

                bool                mFocusable;

                static Widget*      mFocusedWidget;

                static Widget*      mHoveredWidget;

                KeyListeners        mKeyListeners;

                MouseListeners      mMouseListeners;

                Widget*             mParent;

                Vector2f            mSize;

                bool                mUseScissor;

                bool                mVisible;

        };

    }


}

#endif // WIDGET_HPP_INCLUDED
