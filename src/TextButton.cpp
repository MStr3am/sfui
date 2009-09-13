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

#include "TextButton.hpp"
#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace sf
{
    namespace ui
    {
        TextButton::TextButton(const Unicode::Text& caption)
            :   ImageButton(),
                mCaption(caption)
        {
            Add(&mCaption);

            SetDefaultStyle("BI_TextButton");
            LoadStyle(GetDefaultStyle());
        }

        void    TextButton::LoadStyle(const std::string& nameStyle)
        {
            ImageButton::LoadStyle(nameStyle);

            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));
            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));

            mCaption.LoadStyle(nameStyle + "->Label");
        }

        void    TextButton::SetTextColor(const Color& color)
        {
            mCaption.SetTextColor(color);
        }

        const Color&    TextButton::GetTextColor() const
        {
            return mCaption.GetTextColor();
        }

        void    TextButton::SetTextSize(float size)
        {
            mCaption.SetTextSize(size);
        }

        float   TextButton::GetTextSize() const
        {
            return mCaption.GetTextSize();
        }

        void    TextButton::OnPressed()
        {
            mCaption.Move(1.f, 1.f);
            ImageButton::OnPressed();
        }

        void    TextButton::OnReleased()
        {
            mCaption.Move(-1.f, -1.f);
            ImageButton::OnReleased();
        }

        void    TextButton::OnMouseLeft(const Event::MouseMoveEvent& mouse)
        {
            if (IsPressed())
                mCaption.Move(-1.f, -1.f);
            ImageButton::OnMouseLeft(mouse);
        }

        void    TextButton::Render(RenderTarget& target) const
        {
            const Vector2f& absPos = GetAbsolutePosition();

            glEnable(GL_SCISSOR_TEST);
            glScissor(absPos.x, target.GetHeight() - GetHeight() - absPos.y, GetWidth(), GetHeight());

            Widget::Render(target);

            glDisable(GL_SCISSOR_TEST);
        }

    }
}
