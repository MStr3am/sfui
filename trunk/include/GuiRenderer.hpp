#ifndef GUIRENDERER_HPP_INCLUDED
#define GUIRENDERER_HPP_INCLUDED

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

#include <SFML/Graphics/RenderWindow.hpp>

#include "Widget.hpp"

namespace sf
{
    namespace ui
    {
        typedef     Vector2<unsigned int>   Vector2ui;

        class GuiRenderer
        {
            public:
                GuiRenderer(RenderWindow& renderWindow);
                ~GuiRenderer();

                virtual void        InjectEvent(const Event& event);

                void                Resize(const Vector2ui& size);
                void                Resize(unsigned int width, unsigned int height);

                virtual void        Display();

                Widget&             GetTopWidget();

                void                SetFocusedWidget(Widget* widget);
                Widget*             GetFocusedWidget() const;

                Widget*             GetHoveredWidget() const;

            protected:
                void                HandleFocus();

                View                mView;

            private:
                void                SetHoveredWidget(Widget* widget, const Vector2ui& mouse, Vector2f initialPosition);

                RenderWindow&       mRenderWindow;
                Widget              mTopWidget;
                bool                mMouseInside;
        };

    }

}

#endif // GUIRENDERER_HPP_INCLUDED
