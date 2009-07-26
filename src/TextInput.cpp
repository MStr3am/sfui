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
        float    TextInput::mStringOffset = 4.f;

        TextInput::TextInput(const Unicode::Text& string)
            :   Widget(),
                mString(string),
                mMaxLength(0),
                mCursorPosition(0),
                mCursorOffset(0)
        {
            mString.SetFocusable(false);

            Add(&mString);
            AddKeyListener(this);
            AdjustRect();
        }

        void    TextInput::SetText(const Unicode::Text& text)
        {
            mString.SetCaption(text);
        }

        const Unicode::Text& TextInput::GetText() const
        {
            return mString.GetString().GetText();
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

        void    TextInput::OnKeyPressed(const Event::KeyEvent& key)
        {
            std::wstring text = GetText();

            if (key.Code == Key::Left && mCursorPosition)
                --mCursorPosition;
            else if (key.Code == Key::Right && mCursorPosition < text.length())
                ++mCursorPosition;
            else if (key.Code == Key::Home)
                mCursorPosition = 0;
            else if (key.Code == Key::End)
                mCursorPosition = text.length();

            AdjustRect();
        }

        void    TextInput::OnTextEntered(const Event::TextEvent& text)
        {
            std::wstring currentText = GetText();

            switch (text.Unicode)
            {
                case 8:
                    if (!currentText.empty() && mCursorPosition)
                    {
                        currentText.erase(mCursorPosition - 1, 1);
                        --mCursorPosition;
                    }
                break;

                case 127:
                    if (!currentText.empty() && mCursorPosition < currentText.length())
                    {
                        currentText.erase(mCursorPosition, 1);
                    }
                break;

                default :
                    if (currentText.length() < mMaxLength || !mMaxLength)
                    {
                        std::wstring c(L"");
                        c += text.Unicode;
                        currentText.insert(mCursorPosition, c);
                        ++mCursorPosition;
                    }
                break;
            };

            SetText(currentText);

            AdjustRect();
        }

        void    TextInput::AdjustRect()
        {
            // temporary new text for getting size
            const String&   str = mString.GetString();
            const std::wstring& textSaved = str.GetText();

            mString.SetCaption(textSaved.substr(0, mCursorPosition));
            const FloatRect& rect = str.GetRect();
            mString.SetCaption(textSaved);

            if (rect.GetWidth() - mCursorOffset >= GetWidth() - mStringOffset)
            {
                mCursorOffset = rect.GetWidth() - GetWidth() + mStringOffset;
            }
            else if (rect.GetWidth() - mCursorOffset <= 0)
            {
                mCursorOffset = rect.GetWidth() - GetWidth() / (mStringOffset / 2);

            }

            if (mCursorOffset < 0)
                mCursorOffset = 0;

            mString.SetX(mStringOffset - mCursorOffset);
        }

        void    TextInput::Render(RenderTarget& target) const
        {
            const Vector2f& absPos = GetAbsolutePosition();

            glEnable(GL_SCISSOR_TEST);
            glScissor(absPos.x, target.GetHeight() - GetHeight() - absPos.y, GetWidth(), GetHeight());

            Widget::Render(target);

            // Draws the cursor with real position
            if (HasFocus())
            {
                const String&   rStr = mString.GetString();
                float factor = rStr.GetSize() / rStr.GetFont().GetCharacterSize();
                glScalef(factor, factor, 1.f);

                Vector2f realPos(0.f, (GetHeight() - 2.f) / factor);

                const Vector2f& pos = rStr.GetCharacterPos(mCursorPosition);
                realPos.x = (pos.x - mCursorOffset + mStringOffset) / factor;

                glDisable(GL_TEXTURE_2D);

                glBegin(GL_LINES);
                    glVertex2f(realPos.x, 2.f / factor);
                    glVertex2f(realPos.x, realPos.y);
                glEnd();
            }

            glDisable(GL_SCISSOR_TEST);
        }



    }


}
