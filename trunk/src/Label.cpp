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

#include <SFML/Graphics/RenderTarget.hpp>

#include <SFUI/Label.hpp>
#include <SFUI/ResourceManager.hpp>

namespace sf
{
    namespace ui
    {

        Label::Label(const Unicode::Text& caption)
            :   Widget(),
                mCaption(caption, Font::GetDefaultFont(), 30.f)
        {
            SetDefaultStyle("BI_Label");
            LoadStyle(GetDefaultStyle());
        }

        void    Label::SetText(const Unicode::Text& caption)
        {
            mCaption.SetText(caption);

            const Vector2f& strSize = mCaption.GetRect().GetSize();

            if (strSize.x > GetWidth())
                SetWidth(strSize.x);
            if (strSize.y > GetHeight())
                SetHeight(strSize.y);

            UpdatePosition();
        }

        const Unicode::Text&    Label::GetText() const
        {
            return mCaption.GetText();
        }

        void    Label::SetFont(const Font& font)
        {
            mCaption.SetFont(font);
        }

        const Font& Label::GetFont() const
        {
            return mCaption.GetFont();
        }

        void    Label::SetTextSize(float size)
        {
            mCaption.SetSize(size);

            const Vector2f& strSize = mCaption.GetRect().GetSize();

            if (strSize.x > GetWidth())
                SetWidth(strSize.x);
            if (strSize.y > GetHeight())
                SetHeight(strSize.y);
        }

        float   Label::GetTextSize() const
        {
            return mCaption.GetSize();
        }

        void    Label::SetTextColor(const Color& color)
        {
            mCaption.SetColor(color);
        }

        const Color&    Label::GetTextColor() const
        {
            return mCaption.GetColor();
        }

        const String&   Label::GetString() const
        {
            return mCaption;
        }

        void    Label::LoadStyle(const std::string& nameStyle)
        {
            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));

            Font* newFont = rm->GetFont(properties["font"], GetTextSize());
            if (newFont)
            {
                SetFont(*newFont);
            }

            if (properties["textSize"] != "")
            {
                mCaption.SetSize(rm->GetValue(properties["textSize"], GetTextSize()));

                const Vector2f& strSize = mCaption.GetRect().GetSize();

                if (properties["width"] == "")
                    SetWidth(strSize.x);
                if (properties["height"] == "")
                    SetHeight(strSize.y);
            }

            Widget::LoadStyle(nameStyle);
        }

        void    Label::OnPaint(RenderTarget& target, RenderQueue& queue) const
        {
            Widget::OnPaint(target, queue);

            queue.SetColor(GetTextColor());
            target.Draw(mCaption);
        }
    }
}
