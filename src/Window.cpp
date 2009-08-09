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

#include "Window.hpp"

namespace sf
{
    namespace ui
    {
        Window::Window(const Unicode::Text& title)
            :   MovableWidget(),
                mTitle(title)
        {
            mTitle.LoadTemplate("BI_Window_Title");
            LoadTemplate("BI_Window");

            Add(&mTitle);
        }

        void    Window::SetTitle(const Unicode::Text& text)
        {
            mTitle.SetText(text);
        }

        const Unicode::Text&    Window::GetTitle() const
        {
            return mTitle.GetText();
        }

        void    Window::LoadTemplate(const std::string& nameTpl)
        {
            MovableWidget::LoadTemplate(nameTpl);

            mTitle.SetX((GetWidth() - mTitle.GetWidth()) / 2);
        }

    }

}
