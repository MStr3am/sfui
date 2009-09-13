#ifndef TEXTINPUT_HPP_INCLUDED
#define TEXTINPUT_HPP_INCLUDED

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

#include "Label.hpp"
#include "KeyListener.hpp"
#include "MouseListener.hpp"

namespace sf
{
    namespace ui
    {
        class TextInput : public Widget, public KeyListener, public MouseListener
        {
            public :
                TextInput(const Unicode::Text& text = std::wstring(L""));

                void                        SetText(const Unicode::Text& text);
                const Unicode::Text&        GetText() const;

                bool                        IsEmpty() const;

                void                        SetTextColor(const Color& color);
                const Color&                GetTextColor() const;

                void                        SetTextSize(float size);
                float                       GetTextSize() const;

                void                        SetFont(const Font& font);
                const Font&                 GetFont() const;

                void                        SetMaxLength(unsigned int maxLength);
                unsigned int                GetMaxLength() const;

                void                        SetEditable(bool editable = true);
                bool                        IsEditable() const;

                void                        SetSelection(unsigned int start, unsigned int cursorPosition);
                Unicode::Text               GetSelection() const;

                void                        ClearSelection();
                bool                        EraseSelection();

                void                        SetSelectionColor(const Color& color);
                const Color&                GetSelectionColor() const;

                virtual void                LoadStyle(const std::string& nameStyle);

            protected :

                // Inherited from Widget
                virtual void                Render(RenderTarget& target) const;


                // Inherited from KeyListener
                virtual void                OnKeyPressed(const Event::KeyEvent& key);
                virtual void                OnKeyReleased(const Event::KeyEvent& key);
                virtual void                OnTextEntered(const Event::TextEvent& text);

                // Inherited from MouseListener
                virtual void                OnMousePressed(const Event::MouseButtonEvent& button);
                virtual void                OnMouseReleased(const Event::MouseButtonEvent& button);
                virtual void                OnMouseMoved(const Event::MouseMoveEvent& mouse);

                static float                mStringOffset;

            private :
                void                        AdjustRect();
                unsigned int                GetCharacterAtPos(float xOffset);
                unsigned int                GetSelectionSize() const;

                Label                       mString;

                unsigned int                mMaxLength;
                bool                        mEditable;

                unsigned int                mCursorPosition;
                int                         mCursorOffset;

                bool                        mSelectionDragged;
                bool                        mSelectionShifted;
                unsigned int                mSelectionStart;
                Color                       mSelectionColor;


        };



    }

}

#endif // TEXTINPUT_HPP_INCLUDED
