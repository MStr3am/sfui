/*
    This file is part of SFUI (by Robin RUAUX).

    SFUI is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SFUI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SFUI.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Label.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/OpenGL.hpp>

#include "ResourceManager.hpp"

namespace sf
{
    namespace ui
    {

        Label::Label(const Unicode::Text& caption)
            :   Widget(),
                mCaption(caption, Font::GetDefaultFont(), 30.f)
        {
            SetDefaultTemplate("BI_Label");
            LoadTemplate(GetDefaultTemplate());
        }

        void    Label::SetText(const Unicode::Text& caption)
        {
            mCaption.SetText(caption);

            const FloatRect& rect = mCaption.GetRect();

            if (rect.GetWidth() > GetWidth())
                SetWidth(rect.GetWidth());
            if (rect.GetHeight() > GetHeight())
                SetHeight(rect.GetHeight());
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

        void    Label::LoadTemplate(const std::string& nameTpl)
        {
            ResourceManager* rm = ResourceManager::Get();
            TemplateProperties& properties = rm->GetTemplate(nameTpl);

            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));

            if (properties["font"] != "")
            {
                SetFont(*rm->GetFont(properties["font"], GetTextSize()));
            }

            if (properties["textSize"] != "")
            {
                SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));

                const FloatRect& rect = mCaption.GetRect();

                if (properties["width"] == "")
                    SetWidth(rect.GetWidth());
                if (properties["height"] == "")
                    SetHeight(rect.GetHeight());
            }

            Widget::LoadTemplate(nameTpl);
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
