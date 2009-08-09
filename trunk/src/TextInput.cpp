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
                mSelectionStart(0)
        {
            LoadTemplate("BI_TextInput");

            Add(&mString);
            AdjustRect();

            AddKeyListener(this);
            AddMouseListener(this);
        }

        void    TextInput::SetText(const Unicode::Text& text)
        {
            mString.SetText(text);
        }

        const Unicode::Text& TextInput::GetText() const
        {
            return mString.GetText();
        }

        void    TextInput::LoadTemplate(const std::string& nameTpl)
        {
            Widget::LoadTemplate(nameTpl);

            ResourceManager* rm = ResourceManager::Get();
            TemplateProperties& properties = rm->GetTemplate(nameTpl);

            SetMaxLength(rm->GetValue(properties["maxLength"], GetMaxLength()));
            SetSelectionColor(rm->GetColorValue(properties["selectionColor"], GetSelectionColor()));

            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));
            SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));

            if (properties["font"] != "")
            {
                SetFont(*rm->GetFont(properties["font"], GetTextSize()));
            }

            mString.SetY((GetHeight() - mString.GetString().GetSize()) / 2 - 2);
        }

        void    TextInput::SetMaxLength(unsigned int maxLength)
        {
            mMaxLength = maxLength;
        }

        unsigned int    TextInput::GetMaxLength() const
        {
            return mMaxLength;
        }

        void            TextInput::SetTextColor(const Color& color)
        {
            mString.SetTextColor(color);
        }

        const Color&    TextInput::GetTextColor() const
        {
            return mString.GetTextColor();
        }

        void            TextInput::SetTextSize(float size)
        {
            mString.SetTextSize(size);
        }

        float           TextInput::GetTextSize() const
        {
            return mString.GetTextSize();
        }

        void            TextInput::SetFont(const Font& font)
        {
            mString.SetFont(font);
        }

        const Font&     TextInput::GetFont() const
        {
            return mString.GetFont();
        }

        void            TextInput::ClearSelection()
        {
            mSelectionStart = mCursorPosition;
        }

        void            TextInput::SetSelection(unsigned int start, unsigned int cursorPosition)
        {
            const Unicode::UTF16String& text = GetText();

            mSelectionStart = start;
            mCursorPosition = (cursorPosition > text.length()) ? text.length() : cursorPosition;
        }

        void            TextInput::SetSelectionColor(const Color& color)
        {
            mSelectionColor = color;
        }

        const Color&    TextInput::GetSelectionColor() const
        {
            return mSelectionColor;
        }

        Unicode::Text   TextInput::GetSelection() const
        {
            const Unicode::UTF16String& text = GetText();
            return text.substr(std::min(mSelectionStart, mCursorPosition), GetSelectionSize());
        }

        unsigned int    TextInput::GetSelectionSize() const
        {
            if (mSelectionStart < mCursorPosition)
                return mCursorPosition - mSelectionStart;
            return mSelectionStart - mCursorPosition;
        }

        unsigned int    TextInput::GetCharacterAtPos(float xOffset)
        {
            const Unicode::UTF16String& text = GetText();

            for (unsigned int i = 0; i < text.length(); ++i)
            {
                mString.SetText(text.substr(0, i));
                const FloatRect& rect = mString.GetString().GetRect();
                mString.SetText(text);

                if (rect.GetWidth() > xOffset)
                    return i;
            }
            return text.length();
        }

        void    TextInput::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            mCursorPosition = GetCharacterAtPos(button.X - GetAbsolutePosition().x - mStringOffset + mCursorOffset);
            mSelectionDragged = true;
            ClearSelection();

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
                ClearSelection();
            }
            else if (key.Code == Key::Right)
            {
                if (mCursorPosition < text.length())
                    ++mCursorPosition;
                ClearSelection();
            }
            else if (key.Code == Key::Home)
            {
                mCursorPosition = 0;
                ClearSelection();
            }
            else if (key.Code == Key::End)
            {
                mCursorPosition = text.length();
                ClearSelection();
            }
            AdjustRect();
        }

        void    TextInput::OnTextEntered(const Event::TextEvent& text)
        {
            Unicode::UTF16String currentText = GetText();
            bool    selectionDeleted = false;

            if (mSelectionStart != mCursorPosition)
            {
                unsigned int newPos = std::min(mSelectionStart, mCursorPosition);
                currentText.erase(newPos, GetSelectionSize());
                mCursorPosition = newPos;
                selectionDeleted = true;
            }

            if (text.Unicode == 8)
            {
                if (!currentText.empty() && mCursorPosition && !selectionDeleted)
                {
                    currentText.erase(mCursorPosition - 1, 1);
                    --mCursorPosition;
                }
            }
            else if (text.Unicode == 127)
            {
                if (mCursorPosition < currentText.length() && !selectionDeleted)
                    currentText.erase(mCursorPosition, 1);
            }
            else if (currentText.length() < mMaxLength || !mMaxLength)
            {
                Unicode::UTF16String c;
                c += text.Unicode;
                currentText.insert(mCursorPosition, c);
                ++mCursorPosition;
            }

            SetText(currentText);
            ClearSelection();
            AdjustRect();
        }

        void    TextInput::AdjustRect()
        {
            const Unicode::UTF16String& text = GetText();

            mString.SetText(text.substr(0, mCursorPosition));
            const FloatRect& rect = mString.GetString().GetRect();
            mString.SetText(text);

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
                if (mSelectionStart != mCursorPosition)
                {
                    Vector2f selectionPos(rStr.GetCharacterPos(mSelectionStart).x, rStr.GetCharacterPos(mCursorPosition).x);
                    selectionPos.x = (selectionPos.x - mCursorOffset + mStringOffset) / factor;
                    selectionPos.y = (selectionPos.y - mCursorOffset + mStringOffset) / factor;

                    const Color& col = mSelectionColor;
                    glColor4ub(col.r , col.g , col.b, col.a);

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
