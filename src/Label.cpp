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
#include <SFML/Window/OpenGL.hpp>

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

/* sfml 2   const Vector2f& strSize = mCaption.GetRect().GetSize();

            if (strSize.x > GetWidth())
                SetWidth(strSize.x);
            if (strSize.y > GetHeight())
                SetHeight(strSize.y);*/

            const FloatRect& rect = mCaption.GetRect();

            if (rect.GetWidth() > GetWidth())
                SetWidth(rect.GetWidth());
            if (rect.GetHeight() > GetHeight())
                SetHeight(rect.GetHeight());

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
                SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));

/* sfml 2       const Vector2f& strSize = mCaption.GetRect().GetSize();

                if (properties["width"] == "")
                    SetWidth(strSize.x);
                if (properties["height"] == "")
                    SetHeight(strSize.y);
                */

                const FloatRect& rect = mCaption.GetRect();

                if (properties["width"] == "")
                    SetWidth(rect.GetWidth());
                if (properties["height"] == "")
                    SetHeight(rect.GetHeight());
            }

            Widget::LoadStyle(nameStyle);
        }

        void    Label::OnPaint(RenderTarget& target) const
        {
            Widget::OnPaint(target);

            const Unicode::UTF32String& Text = mCaption.GetText();
            const Font& font = mCaption.GetFont();

            float CharSize =  static_cast<float>(font.GetCharacterSize());
            float Factor   = mCaption.GetSize() / CharSize;
            const Color& color = mCaption.GetColor();

            glColor4ub(color.r, color.g, color.b, color.a);
            glScalef(Factor, Factor, 1.f);

            font.GetImage().Bind();

            float X = 0.f;
            float Y = CharSize;

            glBegin(GL_QUADS);

            // Adapted from sf::String (originally coded by Laurent Gomila - SFML)
            for (std::size_t i = 0; i < Text.size(); ++i)
            {
                Uint32           CurChar  = Text[i];
                const Glyph&     CurGlyph = font.GetGlyph(CurChar);
                int              Advance  = CurGlyph.Advance;
                const IntRect&   Rect     = CurGlyph.Rectangle;
                const FloatRect& Coord    = CurGlyph.TexCoords;

                switch (CurChar)
                {
                    case L' ' :  X += Advance;                  continue;
                    case L'\n' : Y += CharSize; X = 0;          continue;
                    case L'\t' : X += font.GetGlyph(' ').Advance * 4;   continue;
                    case L'\v' : Y += CharSize * 4;             continue;
                }

                glTexCoord2f(Coord.Left,  Coord.Top);    glVertex2f(X + Rect.Left, Y + Rect.Top);
                glTexCoord2f(Coord.Left,  Coord.Bottom); glVertex2f(X + Rect.Left, Y + Rect.Bottom);
                glTexCoord2f(Coord.Right, Coord.Bottom); glVertex2f(X + Rect.Right, Y + Rect.Bottom);
                glTexCoord2f(Coord.Right, Coord.Top);    glVertex2f(X + Rect.Right, Y + Rect.Top);

                X += Advance;
            }
            glEnd();
        }
    }
}
