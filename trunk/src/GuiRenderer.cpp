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

#include <SFML/Window/OpenGL.hpp>
#include <SFUI/GuiRenderer.hpp>

#include <SFUI/ResourceManager.hpp>

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

            ResourceManager::Get()->AddStylesFromFile("./data/test.xml");
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

            glEnable(GL_SCISSOR_TEST);
            mRenderWindow.Draw(mTopWidget);
            glDisable(GL_SCISSOR_TEST);

            mRenderWindow.SetView(otherView);
        }

    }

}
