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

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <SFUI/TextInput.hpp>

namespace sf
{
    namespace ui
    {
        float    TextInput::mStringOffset = 4.f;

        TextInput::TextInput(const Unicode::Text& string)
            :   Widget(),
                mString(string),
                mMaxLength(0),
                mEditable(true),
                mCursorPosition(0),
                mCursorOffset(0),
                mSelectionDragged(false),
                mSelectionShifted(false),
                mSelectionStart(0)
        {
            SetDefaultStyle("BI_TextInput");
            LoadStyle(GetDefaultStyle());

            Add(&mString);
            AdjustRect();

            AddKeyListener(this);
            AddMouseListener(this);

            UseScissor(true);
        }

        void    TextInput::SetText(const Unicode::Text& text)
        {
            mString.SetText(text);
        }

        const Unicode::Text& TextInput::GetText() const
        {
            return mString.GetText();
        }

        bool    TextInput::IsEmpty() const
        {
            return (Unicode::UTF16String(mString.GetText()).size() == 0);
        }

        void    TextInput::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            SetMaxLength(rm->GetValue(properties["maxLength"], GetMaxLength()));
            SetEditable(rm->GetValue(properties["editable"], IsEditable()));

            SetSelectionColor(rm->GetColorValue(properties["selectionColor"], GetSelectionColor()));

            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));
            SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));

            Font* newFont = rm->GetFont(properties["font"], GetTextSize());
            if (newFont)
            {
                SetFont(*newFont);
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

        void            TextInput::SetEditable(bool editable)
        {
            mEditable = editable;
        }

        bool            TextInput::IsEditable() const
        {
            return mEditable;
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

        bool            TextInput::EraseSelection()
        {
            if (mSelectionStart == mCursorPosition)
                return false;

            Unicode::UTF16String currentText = GetText();
            unsigned int newPos = std::min(mSelectionStart, mCursorPosition);

            currentText.erase(newPos, GetSelectionSize());
            SetText(currentText);

            mSelectionStart = mCursorPosition = newPos;
            return true;
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

                if (rect.GetSize().x > xOffset)
                    return i;
            }
            return text.length();
        }

        void    TextInput::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (button.Button != Mouse::Left)
                return;

            mCursorPosition = GetCharacterAtPos(button.X - GetAbsolutePosition().x - mStringOffset + mCursorOffset);
            mSelectionDragged = true;
            ClearSelection();

            AdjustRect();
        }

        void    TextInput::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            if (button.Button != Mouse::Left)
                return;

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
            Unicode::UTF16String text = GetText();

            if (key.Code == Key::Left)
            {
                if (mCursorPosition)
                    --mCursorPosition;

                if (!mSelectionShifted)
                    ClearSelection();
            }
            else if (key.Code == Key::Right)
            {
                if (mCursorPosition < text.length())
                    ++mCursorPosition;

                if (!mSelectionShifted)
                    ClearSelection();
            }
            else if (key.Code == Key::Home)
            {
                if (mSelectionShifted)
                {
                    mSelectionStart = mCursorPosition;
                    mCursorPosition = 0;
                }
                else
                {
                    mCursorPosition = 0;
                    ClearSelection();
                }
            }
            else if (key.Code == Key::End)
            {
                if (mSelectionShifted)
                {
                    mSelectionStart = mCursorPosition;
                    mCursorPosition = text.length();
                }
                else
                {
                    mCursorPosition = text.length();
                    ClearSelection();
                }
            }
            else if (key.Code == Key::LShift || key.Code == Key::RShift)
            {
                mSelectionShifted = true;
            }
            else if ((key.Code == Key::Delete || key.Code == Key::Back) && mEditable)
            {
                if (!EraseSelection())
                {
                    if (key.Code == Key::Back && !text.empty() && mCursorPosition)
                    {
                        text.erase(--mCursorPosition, 1);
                    }
                    else if (key.Code == Key::Delete && mCursorPosition < text.length())
                    {
                        text.erase(mCursorPosition, 1);
                    }
                    ClearSelection();
                    SetText(text);
                }
            }
            AdjustRect();
        }

        void    TextInput::OnKeyReleased(const Event::KeyEvent& key)
        {
            if (key.Code == Key::LShift || key.Code == Key::RShift)
            {
                mSelectionShifted = false;
            }
        }

        void    TextInput::OnTextEntered(const Event::TextEvent& text)
        {
            // ASCII non printable caracters have to be ignored.
            if (text.Unicode <= 30 || (text.Unicode >= 127 && text.Unicode <= 159) || !mEditable)
                return;

            EraseSelection();

            Unicode::UTF16String currentText = GetText();

            if (currentText.length() < mMaxLength || !mMaxLength)
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

            const Vector2f& strSize = mString.GetString().GetRect().GetSize();

            if (strSize.x - mCursorOffset >= GetWidth() - mStringOffset)
            {
                mCursorOffset = strSize.x - GetWidth() + mStringOffset;
            }
            else if (strSize.x - mCursorOffset <= 0)
            {
                mCursorOffset = strSize.x - GetWidth() / (mStringOffset / 2);
            }

            mString.SetText(text);


            if (mCursorOffset < 0)
                mCursorOffset = 0;

            mString.SetX(mStringOffset - mCursorOffset);
        }

        void    TextInput::OnPaint(RenderTarget& target, RenderQueue& queue) const
        {
            Widget::OnPaint(target, queue);

            // Draws the cursor with real position
            if (HasFocus())
            {
                const String& rStr = mString.GetString();
                float factor = rStr.GetSize() / rStr.GetFont().GetCharacterSize();
                float yPos = 2.f;

                Vector2f realPos = rStr.GetCharacterPos(mCursorPosition);
                realPos.x = realPos.x - mCursorOffset + mStringOffset;
                realPos.y = GetHeight() - 2.f;

                queue.SetColor(GetTextColor());
                target.Draw(Shape::Rectangle(realPos.x, yPos, realPos.x + 1, realPos.y, GetTextColor()));

                // Draws the current selection
                if (mSelectionStart != mCursorPosition)
                {
                    Vector2f selectionPos(rStr.GetCharacterPos(mSelectionStart).x, rStr.GetCharacterPos(mCursorPosition).x);
                    selectionPos.x = (selectionPos.x - mCursorOffset + mStringOffset);
                    selectionPos.y = (selectionPos.y - mCursorOffset + mStringOffset);

                    queue.SetColor(mSelectionColor);
                    queue.SetTexture(0);

                    queue.BeginBatch();
                    {
                        queue.AddVertex(selectionPos.x, yPos);
                        queue.AddVertex(selectionPos.y, yPos);
                        queue.AddVertex(selectionPos.y, realPos.y);
                        queue.AddVertex(selectionPos.x, realPos.y);

                        queue.AddTriangle(0, 1, 3);
                        queue.AddTriangle(3, 1, 2);
                    }
                }

            }

        }

    }

}
