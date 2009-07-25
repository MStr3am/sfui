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

#include "TextInput.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/OpenGL.hpp>

#include <iostream>

namespace sf
{
    namespace ui
    {
        TextInput::TextInput(const Unicode::Text& string)
            :   Widget(),
                mString(string),
                mMaxLength(0),
                mCursorPosition(0)
        {
            mString.SetFocusable(false);
            mString.SetX(4);

            Add(&mString);
            AddKeyListener(this);
        }

        void    TextInput::SetText(const Unicode::Text& text)
        {
            mString.SetCaption(text);
        }

        const Unicode::Text& TextInput::GetText() const
        {
            return mString.GetCaption();
        }

        void    TextInput::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mString.SetY((GetHeight() - mString.GetSize().y) / 2 - 2);
            }
        }

        void    TextInput::SetMaxLength(unsigned int maxLength)
        {
            mMaxLength = maxLength;
        }

        unsigned int    TextInput::GetMaxLength() const
        {
            return mMaxLength;
        }

        void    TextInput::OnKeyPressed(const Event& event)
        {
            if (event.Key.Code == Key::Left && mCursorPosition)
                --mCursorPosition;
            else if (event.Key.Code == Key::Right)
                ++mCursorPosition;
        }

        void    TextInput::OnTextEntered(const Event& event)
        {
            std::wstring currentText = GetText();

            switch (event.Text.Unicode)
            {
                case 8:
                    if (!currentText.empty())
                        currentText.erase(currentText.length() - 1, 1);
                break;

                default :
                    if (currentText.length() < mMaxLength || !mMaxLength)
                        currentText += event.Text.Unicode;
                break;
            };

            SetText(currentText);
        }

        void    TextInput::OnPaint(RenderTarget& target) const
        {
            const Vector2f& absPos = GetAbsolutePosition();

            glScissor(absPos.x, target.GetHeight() - GetHeight() - absPos.y, GetWidth(), GetHeight());
            Widget::OnPaint(target);
        }



    }


}
