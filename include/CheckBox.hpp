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

#include "Label.hpp"
#include "TextButton.hpp"

namespace sf
{
    namespace ui
    {
        class CheckBox : public Widget, public MouseListener
        {
            public :
                CheckBox(const Unicode::Text& caption);

                void                    SetChecked(bool checked = true);
                bool                    IsChecked() const;

                void                    SetText(const Unicode::Text& caption);
                const Unicode::Text&    GetText() const;

                void                    SetFont(const Font& font);
                const Font&             GetFont() const;

                void                    SetTextColor(const Color& color);
                const Color&            GetTextColor() const;

                virtual void            LoadStyle(const std::string& nameStyle);

            protected :
                // Inherited from MouseListener
                virtual void            OnMousePressed(const Event::MouseButtonEvent& mouse);

                // Inherited from Widget
                virtual void            Render(RenderTarget& target) const;

            private :
                bool                    mChecked;

                GridDecorator           mDecorator;
                Label                   mCaption;
                Icon                    mCheckIcon;

        };

    }

}

#endif // CHECKBOX_HPP_INCLUDED
