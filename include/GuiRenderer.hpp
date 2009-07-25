#ifndef GUIRENDERER_HPP_INCLUDED
#define GUIRENDERER_HPP_INCLUDED

/*
    This file is part of ReGen (by Robin RUAUX).

    ReGen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ReGen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ReGen.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <SFML/Graphics/RenderWindow.hpp>

#include "Widget.hpp"

namespace sf
{
    class GuiRenderer
    {
        public:
            GuiRenderer(RenderWindow& renderWindow);
            ~GuiRenderer();

            void    InjectEvent(const Event& event);

            void    Resize(const Vector2<unsigned int>& size);
            void    Resize(unsigned int width, unsigned int height);

            void    Display();

            Widget& GetTopWidget();
            Widget* GetFocusedWidget() const;

        protected:
            void    HandleFocus();

            View            mView;

        private:
            bool    SetFocusUnderMouse(Widget* widget, const Vector2<unsigned int>& mouse, Vector2f initialPosition);

            RenderWindow&   mRenderWindow;
            Widget          mTopWidget;
            bool            mMouseInside;


    };


}

#endif // GUIRENDERER_HPP_INCLUDED
