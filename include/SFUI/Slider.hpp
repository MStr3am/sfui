#ifndef SLIDER_HPP_INCLUDED
#define SLIDER_HPP_INCLUDED

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

/** \file Slider.hpp
 * \brief Basic slider widget.
 * \author Robin Ruaux
 */

#include <SFUI/GridDecorator.hpp>
#include <SFUI/MovablePolicy.hpp>

namespace sf
{
    namespace ui
    {
        /** \class Slider
         *
         * \brief A basic Slider widget.
         *S
         */
        class Slider : public Widget, public MouseListener
        {
            public :

                typedef enum
                {
                    HORIZONTAL,
                    VERTICAL
                }   SliderType;


                /** \brief Constructor.
                 *
                 * Constructor of Slider class.
                 */
                Slider(SliderType type);


                /** \brief Set the minimum slider value.
                 *
                 * \param value The new minimum slider value.
                 */
                void    SetMinValue(Uint16 value);


                /** \brief Set the maximum slider value.
                 *
                 * \param value The new maximum slider value.
                 */
                void    SetMaxValue(Uint16 value);


                /** \brief Set the slider value.
                 *
                 * \param value The new slider value.
                 */
                void    SetValue(Uint16 value);


                /** \brief Get the maximum slider value.
                 *
                 * \return The maximum slider value.
                 */
                Uint16  GetMaxValue() const;


                /** \brief Get the minimum slider's value.
                 *
                 * \return The minimum slider value.
                 */
                Uint16  GetMinValue() const;


                /** \brief Get the slider current value.
                 *
                 * \return The slider current value.
                 */
                Uint16  GetValue() const;

            protected :

                virtual void    LoadStyle(const std::string& style);

                virtual void    OnMouseMoved(const Event::MouseMoveEvent& mouse);

                GridDecorator   mDecorator;

                Icon            mSlider;

                MovablePolicy   mSliderMovablePolicy;

            private :

                SliderType      mSliderType;

                Uint16          mMinValue, mMaxValue, mValue;

        };
    }

}

#endif // SLIDER_HPP_INCLUDED
