#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

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

/** \file Window.hpp
 * \brief A basic window widget.
 * \author Robin Ruaux
 */

#include <SFUI/MovableWidget.hpp>
#include <SFUI/Label.hpp>
#include <SFUI/GridDecorator.hpp>

namespace sf
{
    namespace ui
    {
        /** \class Window
         *
         * \brief A basic Window widget.
         */
        class Window : public MovableWidget
        {
            public :

                /** \brief Constructor.
                 *
                 * \param title The window initial title.
                 */
                Window(const Unicode::Text& title);

                /** \brief Get the window title Label.
                 *
                 * \return The window title Label.
                 */
                Label&                  GetTitle();


                virtual void            LoadStyle(const std::string& nameStyle);


                /** \brief Set the window title.
                 *
                 * \param title The new window title Label.
                 */
                void                    SetTitle(const Label& title);

            protected :

                virtual void            OnChange(Widget::Property property);

                GridDecorator           mDecorator;

                Label                   mTitle;

        };

    }


}

#endif // WINDOW_HPP_INCLUDED
