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
#include "ResourceManager.hpp"

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

            Widget::mFocusedWidget = Widget::mHoveredWidget = &mTopWidget;

            ResourceManager::Get()->AddTemplatesFromFile("./data/test.xml");
        }

        GuiRenderer::~GuiRenderer()
        {
            ResourceManager::Kill();
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

        Widget* GuiRenderer::GetHoveredWidget() const
        {
            return Widget::mHoveredWidget;
        }

        void    GuiRenderer::SetHoveredWidget(Widget* widget, const Vector2ui& mouse, Vector2f absPos)
        {
            Widgets&  widgets = widget->mChildren;

            for (Widgets::reverse_iterator it = widgets.rbegin(); it != widgets.rend(); ++it)
            {
                Widget* currentWidget = *it;

                if (currentWidget->IsVisible() && currentWidget->IsFocusable())
                {
                    absPos += currentWidget->GetPosition();

                    if (mouse.x >= absPos.x && mouse.x <= absPos.x + currentWidget->mSize.x &&
                        mouse.y >= absPos.y && mouse.y <= absPos.y + currentWidget->mSize.y)
                    {
                        Widget::mHoveredWidget = currentWidget;
                        SetHoveredWidget(currentWidget, mouse, absPos);
                        return;
                    }
                    absPos -= currentWidget->GetPosition();
                }
            }
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
            // Set the hovered widget
            else if (event.Type == Event::MouseMoved)
            {
                static Widget*  lastHovered = &mTopWidget;

                Widget::mHoveredWidget = &mTopWidget;
                SetHoveredWidget(&mTopWidget, Vector2ui(event.MouseMove.X, event.MouseMove.Y), mTopWidget.GetPosition());

                if (lastHovered != Widget::mHoveredWidget)
                {
                    sf::Event newEvent = event;

                    newEvent.Type = Event::MouseLeft;
                    lastHovered->DistributeEvent(newEvent);

                    newEvent.Type = Event::MouseEntered;
                    Widget::mHoveredWidget->DistributeEvent(newEvent);

                    lastHovered = Widget::mHoveredWidget;
                }
            }
            if (Widget::mFocusedWidget)
                Widget::mFocusedWidget->DistributeEvent(event);
        }


        void    GuiRenderer::HandleFocus()
        {
            if (Widget::mHoveredWidget)
                if (Widget::mHoveredWidget->IsFocusable())
                    Widget::mFocusedWidget = Widget::mHoveredWidget;
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
            const View& otherView = mRenderWindow.GetView();

            mRenderWindow.SetView(mView);
            mRenderWindow.Draw(mTopWidget);
            mRenderWindow.SetView(otherView);
        }

    }

}
