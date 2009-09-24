#ifndef RADIOBUTTON_HPP_INCLUDED
#define RADIOBUTTON_HPP_INCLUDED

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

/** \file RadioButton.hpp
 * \brief RadioButtons and areas.
 * \author Robin Ruaux
 */

#include <SFUI/CheckBox.hpp>

namespace sf
{
    namespace ui
    {
        /** \class RadioButton
         *
         * \brief A basic RadioButton (part of RadioArea).
         */
        class RadioButton : public CheckBox
        {
            public :
                /** \brief Constructor
                 *
                 * Constructor of RadioButton class.
                 * \param caption the radiobutton text.
                 */
                RadioButton(const Unicode::Text& caption);
        };


        /** \typedef std::vector<RadioButton*>   RadioButtons
         *
         * A RadioButton container.
         */
        typedef std::vector<RadioButton*>   RadioButtons;


        /** \class RadioArea
         *
         * \brief A group of RadioButton
         */
        class RadioArea : public Widget, public MouseListener
        {
            public :

                /** \brief Constructor
                 *
                 * Constructor of RadioArea class.
                 */
                RadioArea();

                /** \brief Add a new radiobutton to the area.
                 *
                 * \param radioBtn the radiobutton to be added.
                 */
                void                        AddRadioButton(RadioButton* radioBtn);


                RadioButton*                GetSelectedRadio() const;


                virtual void                LoadStyle(const std::string& nameStyle);

                /** \brief Remove a radiobutton from the area.
                 *
                 * \param radioBtn the radiobutton to be removed.
                 */
                void                        RemoveRadioButton(RadioButton* radioBtn);

            protected :

                virtual void                OnChange(Widget::Property property);

                virtual void                OnMouseReleased(const Event::MouseButtonEvent& mouse);

                GridDecorator               mDecorator;

            private :

                void                        AdjustButtons();

                RadioButtons                mAddedButtons;

                RadioButton*                mSelectedRadio;

        };
    }
}

#endif // RADIOBUTTON_HPP_INCLUDED
