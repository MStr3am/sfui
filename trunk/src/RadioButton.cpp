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

#include <SFUI/RadioButton.hpp>

namespace sf
{
    namespace ui
    {
        RadioButton::RadioButton(const Unicode::Text& caption)
            :   CheckBox(caption)
        {
            SetDefaultStyle("BI_RadioButton");
            LoadStyle(GetDefaultStyle());
        }

        RadioArea::RadioArea()
            :   Widget(),
                mDecorator(),
                mSelectedRadio(0)
        {
            SetDefaultStyle("BI_RadioArea");
            LoadStyle(GetDefaultStyle());

            Add(&mDecorator);
        }

        RadioButton*    RadioArea::GetSelectedRadio() const
        {
            return mSelectedRadio;
        }

        void    RadioArea::OnMouseReleased(const Event::MouseButtonEvent& mouse)
        {
            if (mouse.Button == Mouse::Left)
            {
                // First, we get the selected radioButton
                for (RadioButtons::const_iterator it = mAddedButtons.begin(); it != mAddedButtons.end(); ++it)
                {
                    if ((*it)->IsHovered())
                    {
                        mSelectedRadio = *it;
                        break;
                    }
                }

                if (mSelectedRadio)
                {
                    // Then we deselect all others
                    for (RadioButtons::iterator it = mAddedButtons.begin(); it != mAddedButtons.end(); ++it)
                    {
                        (*it)->SetChecked(false);
                    }
                    mSelectedRadio->SetChecked(true);
                }

            }
        }

        void    RadioArea::AddRadioButton(RadioButton* radioBtn)
        {
            if (!radioBtn)
                return;

            for (RadioButtons::const_iterator it = mAddedButtons.begin(); it != mAddedButtons.end(); ++it)
            {
                if (*it == radioBtn)
                    return;
            }

            Add(radioBtn);
            radioBtn->AddMouseListener(this);
            mAddedButtons.push_back(radioBtn);

            AdjustButtons();
        }

        void    RadioArea::RemoveRadioButton(RadioButton* radioBtn)
        {
            if (!radioBtn)
                return;

            for (RadioButtons::iterator it = mAddedButtons.begin(); it != mAddedButtons.end(); ++it)
            {
                if (*it == radioBtn)
                {
                    Remove(radioBtn);
                    radioBtn->RemoveMouseListener(this);
                    mAddedButtons.erase(it);
                    break;
                }
            }
        }

        void    RadioArea::AdjustButtons()
        {
            unsigned int posY = 0;

            for (RadioButtons::iterator it = mAddedButtons.begin(); it != mAddedButtons.end(); ++it)
            {
                RadioButton* current = *it;

                current->SetY(posY);
                posY += current->GetHeight();
            }

            SetHeight(posY);
        }

        void    RadioArea::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            mDecorator.LoadStyle(nameStyle + "->Background");
        }

        void    RadioArea::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mDecorator.SetSize(GetSize());
            }
            Widget::OnChange(property);
        }

    }
}
