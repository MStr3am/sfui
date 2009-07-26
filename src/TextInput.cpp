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
                mCursorOffset(0),
                mSelectionDragged(false),
                mSelectionIndexes(0, 0)
        {
            mString.SetFocusable(false);

            Add(&mString);
            AdjustRect();

            AddKeyListener(this);
            AddMouseListener(this);
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

        unsigned int    TextInput::GetCharacterAtPos(float xOffset)
        {
            const Unicode::UTF16String& text = GetText();

            for (unsigned int i = 0; i < text.length(); ++i)
            {
                mString.SetCaption(text.substr(0, i));
                const FloatRect& rect = mString.GetString().GetRect();
                mString.SetCaption(text);

                if (rect.GetWidth() > xOffset)
                    return i;
            }
            return text.length();
        }

        void    TextInput::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            mCursorPosition = GetCharacterAtPos(button.X - GetAbsolutePosition().x - mStringOffset + mCursorOffset);
            mSelectionDragged = true;
            mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition;

            AdjustRect();
        }

        void    TextInput::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            if (mSelectionDragged)
                mSelectionDragged = false;
        }

        void    TextInput::OnMouseMoved(const Event::MouseMoveEvent& mouse)
        {
            if (mSelectionDragged)
            {
                mCursorPosition = GetCharacterAtPos(mouse.X - GetAbsolutePosition().x - mStringOffset + mCursorOffset);
                mSelectionIndexes.y = mCursorPosition;

                AdjustRect();
            }
        }

        void    TextInput::OnKeyPressed(const Event::KeyEvent& key)
        {
            const Unicode::UTF16String& text = GetText();

            if (key.Code == Key::Left)
            {
                if (mCursorPosition)
                    --mCursorPosition;
                mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition;
            }
            else if (key.Code == Key::Right)
            {
                if (mCursorPosition < text.length())
                    ++mCursorPosition;
                mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition;
            }
            else if (key.Code == Key::Home)
                mCursorPosition = 0;
            else if (key.Code == Key::End)
                mCursorPosition = text.length();

            AdjustRect();
        }

        void    TextInput::OnTextEntered(const Event::TextEvent& text)
        {
            Unicode::UTF16String currentText = GetText();

            switch (text.Unicode)
            {
                case 8:
                    if (currentText.empty())
                        break;
                    if (mCursorPosition && mSelectionIndexes.x == mSelectionIndexes.y)
                    {
                        currentText.erase(mCursorPosition - 1, 1);
                        --mCursorPosition;
                    }
                    else
                    {
                        currentText.erase(std::min(mSelectionIndexes.x, mSelectionIndexes.y), std::abs(mSelectionIndexes.y - mSelectionIndexes.x));
                        mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition = std::min(mSelectionIndexes.x, mSelectionIndexes.y);
                    }
                break;

                case 127:
                    if (currentText.empty())
                        break;
                    if (mSelectionIndexes.x == mSelectionIndexes.y && mCursorPosition < currentText.length())
                    {
                        currentText.erase(mCursorPosition, 1);
                    }
                    else
                    {
                        currentText.erase(std::min(mSelectionIndexes.x, mSelectionIndexes.y), std::abs(mSelectionIndexes.y - mSelectionIndexes.x));
                        mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition = std::min(mSelectionIndexes.x, mSelectionIndexes.y);
                    }
                break;

                default :
                    if (currentText.length() < mMaxLength || !mMaxLength)
                    {
                        if (mSelectionIndexes.x != mSelectionIndexes.y)
                        {
                            currentText.erase(std::min(mSelectionIndexes.x, mSelectionIndexes.y), std::abs(mSelectionIndexes.y - mSelectionIndexes.x));
                            mSelectionIndexes.x = mSelectionIndexes.y = mCursorPosition = std::min(mSelectionIndexes.x, mSelectionIndexes.y);
                        }

                        Unicode::UTF16String c;
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
            const Unicode::UTF16String& text = GetText();

            mString.SetCaption(text.substr(0, mCursorPosition));
            const FloatRect& rect = mString.GetString().GetRect();
            mString.SetCaption(text);

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
                const String& rStr = mString.GetString();
                float factor = rStr.GetSize() / rStr.GetFont().GetCharacterSize();
                float yPos = 2.f / factor;
                glScalef(factor, factor, 1.f);

                Vector2f realPos = rStr.GetCharacterPos(mCursorPosition);
                realPos.x = (realPos.x - mCursorOffset + mStringOffset) / factor;
                realPos.y = (GetHeight() - 2.f) / factor;

                glDisable(GL_TEXTURE_2D);

                glBegin(GL_LINES);
                    glVertex2f(realPos.x, yPos);
                    glVertex2f(realPos.x, realPos.y);
                glEnd();

                // Draws the current selection
                if (mSelectionIndexes.x != mSelectionIndexes.y)
                {
                    Vector2f selectionPos(rStr.GetCharacterPos(mSelectionIndexes.x).x, rStr.GetCharacterPos(mSelectionIndexes.y).x);
                    selectionPos.x = (selectionPos.x - mCursorOffset + mStringOffset) / factor;
                    selectionPos.y = (selectionPos.y - mCursorOffset + mStringOffset) / factor;

                    const Color& col = mString.GetColor();
                    glColor4f(col.r / 255.f, col.g / 255.f, col.b / 255.f, col.a / 785.f);

                    glBegin(GL_QUADS);
                        glVertex2f(selectionPos.x, yPos);
                        glVertex2f(selectionPos.y, yPos);
                        glVertex2f(selectionPos.y, realPos.y);
                        glVertex2f(selectionPos.x, realPos.y);
                    glEnd();
                }
            }

            glDisable(GL_SCISSOR_TEST);
        }



    }


}
