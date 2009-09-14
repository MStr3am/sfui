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

#include "Button.hpp"

namespace sf
{
    namespace ui
    {
        Button::Button()
            :   Widget(),
                mPressed(false)
        {
            SetDefaultStyle("BI_Button");
            LoadStyle(GetDefaultStyle());

            AddMouseListener(this);
        }

        void    Button::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (!mPressed)
            {
                mPressed = true;
                LoadStyle(GetDefaultStyle() + "_Pressed");
                OnPressed();
            }
        }

        void    Button::OnMouseReleased(const Event::MouseButtonEvent& button)
        {
            if (mPressed)
            {
                mPressed = false;
                LoadStyle(GetDefaultStyle() + "_Hovered");
                OnReleased();
            }
        }

        void    Button::OnMouseEntered(const Event::MouseMoveEvent& mouse)
        {
            LoadStyle(GetDefaultStyle() + "_Hovered");
        }

        void    Button::OnMouseLeft(const Event::MouseMoveEvent& mouse)
        {
            mPressed = false;
            LoadStyle(GetDefaultStyle());
        }

        void    Button::SetPressed(bool pressed)
        {
            mPressed = pressed;
        }

        bool    Button::IsPressed() const
        {
            return mPressed;
        }


    }

}
