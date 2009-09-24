#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

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

/** \file Button.hpp
 * \brief A basic Button widget
 * \author Robin Ruaux
 */

#include <SFUI/Label.hpp>
#include <SFUI/MouseListener.hpp>

namespace sf
{
    namespace ui
    {
        /** \class Button
         *
         * \brief A basic Button widget
         *
         * This very basic class is used as a template for other buttons.
         */
        class Button : public Widget, public MouseListener
        {
            public :

                /** \brief Constructor
                 *
                 * Constructor of Button class.
                 */
                Button();


                /** \brief Check if the button is pressed.
                 *
                 * \return The button pressed state.
                 */
                bool            IsPressed() const;


                /** \brief Set the button state as pressed.
                 *
                 * \param pressed The new pressed state.
                 */
                void            SetPressed(bool pressed = true);

            protected :


                virtual void    OnMouseEntered(const Event::MouseMoveEvent& mouse);

                virtual void    OnMouseLeft(const Event::MouseMoveEvent& mouse);

                virtual void    OnMousePressed(const Event::MouseButtonEvent& button);

                virtual void    OnMouseReleased(const Event::MouseButtonEvent& button);

                /** \brief Called when the button has been pressed */
                virtual void    OnPressed() {};

                /** \brief Class when the button has been released */
                virtual void    OnReleased() {};


            private :

                bool            mPressed;

        };
    }

}

#endif // BUTTON_HPP_INCLUDED
