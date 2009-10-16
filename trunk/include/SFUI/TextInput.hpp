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

/** \file TextInput.hpp
 * \brief A basic text line input.
 * \author Robin Ruaux
 */

#include <SFUI/Label.hpp>
#include <SFUI/KeyListener.hpp>
#include <SFUI/MouseListener.hpp>

namespace sf
{
    namespace ui
    {
        /** \class TextInput
         *
         * \brief A basic TextInput line input.
         */
        class TextInput : public Widget, public KeyListener, public MouseListener
        {
            public :

                /** \brief Constructor
                 *
                 * Constructor of TextInput class.
                 * \param text The textinput initial text.
                 */
                TextInput(const Unicode::Text& text = std::wstring(L""));


                /** \brief Clear the current selection. */
                void                        ClearSelection();


                /** \brief Erase the current text selection */
                bool                        EraseSelection();


                /** \brief Check if the textinput is editable.
                 *
                 * \return The textinput editable state.
                 */
                bool                        IsEditable() const;


                /** \brief Check if the textinput is empty.
                 *
                 * \return true if the textinput is emty.
                 * \return false otherwise.
                 */
                bool                        IsEmpty() const;


                /** \brief Get the textinput text font.
                 *
                 * \return The textinput text font.
                 */
                const Font&                 GetFont() const;


                /** \brief Get the textinput maxlength.
                 *
                 * \return The textinput maxlength.
                 */
                unsigned int                GetMaxLength() const;

                /** \brief Get the textinput selection.
                 *
                 * \return The textinput selection.
                 */
                Unicode::Text               GetSelection() const;

                /** \brief Get the textinput selection color.
                 *
                 * \return The textinput selection color.
                 */
                const Color&                GetSelectionColor() const;


                /** \brief Get the textinput text.
                 *
                 * \return The textinput text.
                 */
                const Unicode::Text&        GetText() const;


                /** \brief Get the textinput text color.
                 *
                 * \return The textinput text color.
                 */
                const Color&                GetTextColor() const;


                /** \brief Get the textinput text size.
                 *
                 * \return The textinput text size.
                 */
                float                       GetTextSize() const;


                virtual void                LoadStyle(const std::string& nameStyle);


                /** \brief Set the textinput to be editable.
                 *
                 * \param editable The textinput editable property.
                 */
                void                        SetEditable(bool editable = true);


                /** \brief Set the textinput font.
                 *
                 * \param font The new textinput font.
                 */
                void                        SetFont(const Font& font);


                /** \brief Set the textinput maxlength.
                 *
                 * \param maxLength The new textinput maxlength.
                 */
                void                        SetMaxLength(unsigned int maxLength);


                /** \brief Set the textinput current selection.
                 *
                 * \param start The text selection start.
                 * \param cursorPosition The position of the cursor in the text.
                 */
                void                        SetSelection(unsigned int start, unsigned int cursorPosition);


                /** \brief Set the textinput selection color.
                 *
                 * \param color The new textinput selection color.
                 */
                void                        SetSelectionColor(const Color& color);


                /** \brief Set the textinput text.
                 *
                 * \param text The new textinput text.
                 */
                void                        SetText(const Unicode::Text& text);


                /** \brief Set the textinput text color.
                 *
                 * \param color The new textinput text color.
                 */
                void                        SetTextColor(const Color& color);


                /** \brief Set the textinput text size.
                 *
                 * \param size The new textinput text size.
                 */
                void                        SetTextSize(float size);


            protected :

                virtual void                OnKeyPressed(const Event::KeyEvent& key);

                virtual void                OnKeyReleased(const Event::KeyEvent& key);

                virtual void                OnMouseMoved(const Event::MouseMoveEvent& mouse);

                virtual void                OnMousePressed(const Event::MouseButtonEvent& button);

                virtual void                OnMouseReleased(const Event::MouseButtonEvent& button);

                virtual void                OnPaint(RenderTarget& target, RenderQueue& queue) const;

                virtual void                OnTextEntered(const Event::TextEvent& text);

                static float                mStringOffset;

            private :

                void                        AdjustRect();

                unsigned int                GetCharacterAtPos(float xOffset);

                unsigned int                GetSelectionSize() const;

                int                         mCursorOffset;

                unsigned int                mCursorPosition;

                bool                        mEditable;

                unsigned int                mMaxLength;

                Color                       mSelectionColor;

                bool                        mSelectionDragged;

                bool                        mSelectionShifted;

                unsigned int                mSelectionStart;

                Label                       mString;

        };

    }

}

#endif // TEXTINPUT_HPP_INCLUDED
