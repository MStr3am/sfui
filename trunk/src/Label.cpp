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

namespace sf
{
    Label::Label(const Unicode::Text& caption, float textSize)
        :   Widget(),
            mCaption(caption, Font::GetDefaultFont(), textSize)
    {
        const FloatRect&    rect = mCaption.GetRect();

        SetSize(rect.GetWidth(), rect.GetHeight());
    }

    void    Label::OnChange(Widget::Property property)
    {
        if (property == Widget::COLOR)
        {
            mCaption.SetColor(GetColor());
        }
    }

    void    Label::OnPaint(RenderTarget& target) const
    {
        const Unicode::UTF32String& Text = mCaption.GetText();
        const Font& font = mCaption.GetFont();

        if (Text.empty())
            return;

        float CharSize =  static_cast<float>(font.GetCharacterSize());
        float Factor   = mCaption.GetSize() / CharSize;
        glScalef(Factor, Factor, 1.f);

        font.GetImage().Bind();

        float X = 0.f;
        float Y = CharSize;

        glBegin(GL_QUADS);

        for (std::size_t i = 0; i < Text.size(); ++i)
        {
            Uint32           CurChar  = Text[i];
            const Glyph&     CurGlyph = font.GetGlyph(CurChar);
            int              Advance  = CurGlyph.Advance;
            const IntRect&   Rect     = CurGlyph.Rectangle;
            const FloatRect& Coord    = CurGlyph.TexCoords;

            switch (CurChar)
            {
                case L' ' :  X += Advance;         continue;
                case L'\n' : Y += CharSize; X = 0; continue;
                case L'\t' : X += Advance  * 4;    continue;
                case L'\v' : Y += CharSize * 4;    continue;
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
