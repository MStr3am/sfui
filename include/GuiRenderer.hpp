#ifndef GUIRENDERER_HPP_INCLUDED
#define GUIRENDERER_HPP_INCLUDED

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
