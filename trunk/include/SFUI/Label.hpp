#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

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

/** \file Label.hpp
 * \brief A basic text widget.
 * \author Robin Ruaux
 */

#include <SFML/Graphics/String.hpp>

#include <SFUI/Widget.hpp>

namespace sf
{
    namespace ui
    {
        /** \class Label
         *
         * \brief A basic Label class
         */
        class Label : public Widget
        {
            public :

                /** \brief Constructor.
                 *
                 * Constructor of Label class.
                 *
                 * \param caption The initial label text.
                 */
                Label(const Unicode::Text& caption);

                /** \brief Set the label text.
                 *
                 * \param caption The new label text.
                 */
                void                    SetText(const Unicode::Text& caption);

                /** \brief Get the label text.
                 *
                 * \return The label text.
                 */
                const Unicode::Text&    GetText() const;

                /** \brief Set the label font.
                 *
                 * \param font The new label font.
                 */
                void                    SetFont(const Font& font);

                /** \brief Get the label font.
                 *
                 * \return The label font.
                 */
                const Font&             GetFont() const;

                /** \brief Set the label text size.
                 *
                 * \param size The new label text size.
                 */
                void                    SetTextSize(float size);

                /** \brief Get the label text size.
                 *
                 * \return The label text size.
                 */
                float                   GetTextSize() const;

                /** \brief Set the label text color.
                 *
                 * \param color The new label text color.
                 */
                void                    SetTextColor(const Color& color);

                /** \brief Get the label text color.
                 *
                 * \return The label text color.
                 */
                const Color&            GetTextColor() const;

                /** \brief Get the sf::String used by the widget implementation */
                const String&           GetString() const;

                virtual void            LoadStyle(const std::string& nameStyle);

            protected :

                virtual void            OnPaint(RenderTarget& target) const;

            private :

                String                  mCaption;

        };

    }

}

#endif // LABEL_HPP_INCLUDED
