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

#include "GuiRenderer.hpp"
#include <SFML/Window/OpenGL.hpp>

namespace sf
{
    namespace ui
    {
        GuiRenderer::GuiRenderer(sf::RenderWindow& renderWindow)
            :   mView(Vector2f(0.f, 0.f), Vector2f(renderWindow.GetWidth(), renderWindow.GetHeight())),
                mRenderWindow(renderWindow),
                mTopWidget(),
                mMouseInside(true)
        {
            Resize(renderWindow.GetWidth(), renderWindow.GetHeight());
            mTopWidget.SetColor(Color(0, 0, 0, 0));
        }

        GuiRenderer::~GuiRenderer()
        {

        }

        Widget& GuiRenderer::GetTopWidget()
        {
            return mTopWidget;
        }

        void    GuiRenderer::SetFocusedWidget(Widget* widget)
        {
            Widget::mFocusedWidget = widget;
        }

        Widget* GuiRenderer::GetFocusedWidget() const
        {
            return Widget::mFocusedWidget;
        }

        void    GuiRenderer::InjectEvent(const Event& event)
        {
            // We left the injection for unwanted events
            if (event.Type == Event::MouseEntered || event.Type == Event::MouseLeft ||
                event.Type == Event::GainedFocus || event.Type == Event::LostFocus)
            {
                return;
            }
            // If the view need to be resized
            else if (event.Type == Event::Resized)
            {
                Resize(event.Size.Width, event.Size.Height);
                return;
            }
            // Handle the focus on click
            else if (event.Type == Event::MouseButtonPressed)
            {
                HandleFocus();
            }

            if (Widget::mFocusedWidget)
            {
                // We have to simulate the MouseEntered and MouseLeft events for Widgets.
                if (event.Type == Event::MouseMoved)
                {
                    const Input& input = mRenderWindow.GetInput();
                    bool inside = Widget::mFocusedWidget->GetRect(true).Contains(input.GetMouseX(), input.GetMouseY());

                    Event newEvent = event;

                    if (inside && !mMouseInside)
                    {
                        newEvent.Type = Event::MouseEntered;
                        mMouseInside = inside;
                    }
                    else if (!inside && mMouseInside)
                    {
                        newEvent.Type = Event::MouseLeft;
                        mMouseInside = inside;
                    }
                    Widget::mFocusedWidget->DistributeEvent(newEvent);
                }
                else
                    Widget::mFocusedWidget->DistributeEvent(event);
            }

        }

        void    GuiRenderer::Resize(const Vector2ui& size)
        {
            Resize(size.x, size.y);
        }

        void    GuiRenderer::Resize(unsigned int width, unsigned int height)
        {
            mTopWidget.SetSize(width, height);
            mView.SetFromRect(FloatRect(0.f, 0.f, width, height));
        }

        void    GuiRenderer::Display()
        {
            mRenderWindow.SetView(mView);

            mRenderWindow.Draw(mTopWidget);

            mRenderWindow.SetView(mRenderWindow.GetDefaultView());
        }


        void    GuiRenderer::HandleFocus()
        {
            const Input& input = mRenderWindow.GetInput();

            Vector2<unsigned int> mousePos(input.GetMouseX(), input.GetMouseY());

            // We detect if the focus have been activated for a widget
            if (!SetFocusUnderMouse(&mTopWidget, mousePos, mTopWidget.GetPosition()))
            {
                Widget::mFocusedWidget = 0;
            }
        }

        bool    GuiRenderer::SetFocusUnderMouse(Widget* widget, const Vector2ui& mouse, Vector2f absPos)
        {
            Widgets&  widgets = widget->mChildren;

            for (Widgets::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
            {
                Widget* currentWidget = *it;

                if (currentWidget->IsFocusable())
                {
                    absPos += currentWidget->GetPosition();

                    if (mouse.x >= absPos.x && mouse.x <= absPos.x + currentWidget->mSize.x &&
                        mouse.y >= absPos.y && mouse.y <= absPos.y + currentWidget->mSize.y)
                    {
                        Widget::mFocusedWidget = currentWidget;
                        mMouseInside = true;
                        SetFocusUnderMouse(currentWidget, mouse, absPos);
                        return true;
                    }
                    absPos -= currentWidget->GetPosition();
                }
            }
            return false;
        }

    }

}
