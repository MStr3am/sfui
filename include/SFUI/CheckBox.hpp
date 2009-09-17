#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

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

/** \file CheckBox.hpp
 * \brief A basic CheckBox widget
 * \author Robin Ruaux
 */

#include <SFUI/Label.hpp>
#include <SFUI/TextButton.hpp>

namespace sf
{
    namespace ui
    {
        /** \class CheckBox
         *
         * \brief A basic CheckBox widget.
         */
        class CheckBox : public Widget, public MouseListener
        {
            public :
                /** \brief Constructor
                 *
                 * Constructor of CheckBox class.
                 *
                 * \param caption The checkbox initial caption.
                 */
                CheckBox(const Unicode::Text& caption);

                /** \brief Set the checkbox state
                 *
                 * \param checked The new checked state.
                 */
                void                    SetChecked(bool checked = true);

                /** \brief Check if the checkbox have been checked.
                 *
                 * \return The checked state.
                 */
                bool                    IsChecked() const;

                /** \brief Set the checkbox caption text.
                 *
                 * \param caption The new checkbox text.
                 */
                void                    SetText(const Unicode::Text& caption);

                /** \brief Get the checkbox caption text.
                 *
                 * \return The checkbox caption text.
                 */
                const Unicode::Text&    GetText() const;

                /** \brief Set the checkbox text font.
                 *
                 * \param font The new checkbox text font.
                 */
                void                    SetFont(const Font& font);

                /** \brief Get the checkbox text font.
                 *
                 * \return The checkbox text font.
                 */
                const Font&             GetFont() const;

                /** \brief Set the checkbox text color.
                 *
                 * \param color The new checkbox text color.
                 */
                void                    SetTextColor(const Color& color);

                /** \brief Get the checkbox text color.
                 *
                 * \return The checkbox text color.
                 */
                const Color&            GetTextColor() const;

                virtual void            LoadStyle(const std::string& nameStyle);

            protected :

                virtual void            OnMouseReleased(const Event::MouseButtonEvent& button);

            private :

                bool                    mChecked;

                GridDecorator           mDecorator;

                Label                   mCaption;

                Icon                    mCheckIcon;

        };

    }

}

#endif // CHECKBOX_HPP_INCLUDED
