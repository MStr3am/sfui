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

#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFUI/CheckBox.hpp>

namespace sf
{
    namespace ui
    {
        CheckBox::CheckBox(const Unicode::Text& caption)
            :   Widget(),
                mChecked(false),
                mDecorator(),
                mCaption(caption),
                mCheckIcon()
        {
            SetDefaultStyle("BI_CheckBox");
            LoadStyle(GetDefaultStyle());

            Add(&mDecorator);
            Add(&mCaption);
            Add(&mCheckIcon);

            //mCheckIcon.AddMouseListener(this);
            AddMouseListener(this);
        }

        void    CheckBox::SetChecked(bool checked)
        {
            mChecked = checked;
            LoadStyle((checked) ? GetDefaultStyle() +  "_Checked" : GetDefaultStyle());
        }

        bool    CheckBox::IsChecked() const
        {
            return mChecked;
        }

        void    CheckBox::OnMouseReleased(const Event::MouseButtonEvent& mouse)
        {
            if (mouse.Button == Mouse::Left)
            {
                if (mChecked)
                {
                    mChecked = false;
                    LoadStyle(GetDefaultStyle());
                }
                else
                {
                    mChecked = true;
                    LoadStyle(GetDefaultStyle() + "_Checked");
                }
            }
        }

        void    CheckBox::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            mDecorator.LoadStyle(nameStyle + "->Background");
            mCheckIcon.LoadStyle(nameStyle + "->Icon");
            mCaption.LoadStyle(nameStyle + "->Label");
        }

        void    CheckBox::SetText(const Unicode::Text& text)
        {
            mCaption.SetText(text);
        }

        const Unicode::Text&    CheckBox::GetText() const
        {
            return mCaption.GetText();
        }

        void    CheckBox::SetFont(const Font& font)
        {
            mCaption.SetFont(font);
        }

        const Font& CheckBox::GetFont() const
        {
            return mCaption.GetFont();
        }

        void    CheckBox::SetTextColor(const Color& color)
        {
            mCaption.SetColor(color);
        }

        const Color&    CheckBox::GetTextColor() const
        {
            return mCaption.GetColor();
        }

    }
}
