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

#include "CheckBox.hpp"
#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{
    namespace ui
    {
        CheckBox::CheckBox(const Unicode::Text& caption)
            :   Widget(),
                mCaption(caption),
                mChecked(false)
        {
            mCaption.SetFocusable(false);
            SetColor(Color(0, 0, 0));

            const FloatRect& rect = mCaption.GetString().GetRect();
            SetSize(rect.GetHeight() + 4.f + rect.GetWidth(), rect.GetHeight());

            Add(&mCaption);
            AddMouseListener(this);
        }

        void    CheckBox::SetText(const Unicode::Text& text)
        {
            mCaption.SetText(text);
        }

        const Unicode::Text&    CheckBox::GetText() const
        {
            return mCaption.GetText();
        }

        void    CheckBox::SetTextColor(const Color& color)
        {
            mCaption.SetColor(color);
        }

        const Color&    CheckBox::GetTextColor() const
        {
            return mCaption.GetColor();
        }

        void    CheckBox::SetChecked(bool checked)
        {
            mChecked = checked;
        }

        bool    CheckBox::IsChecked() const
        {
            return mChecked;
        }

        void    CheckBox::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mCaption.SetX(GetHeight() + 4.f);
                mCaption.SetY((GetHeight() - mCaption.GetSize().y) / 2 - 2);
            }
            else if (property == Widget::ENABLE)
            {
                Color col = mCaption.GetColor();
                static float savedAlpha = col.a;

                if (!IsEnabled())
                {
                    savedAlpha = col.a;
                    col.a = 100;
                }
                else
                    col.a = savedAlpha;

                mCaption.SetColor(col);
            }
        }

        void    CheckBox::OnMousePressed(const Event::MouseButtonEvent& button)
        {
            if (button.Button != Mouse::Left)
                return;
            mChecked = !mChecked;
        }

        void    CheckBox::OnPaint(RenderTarget& target) const
        {
            //Widget::OnPaint(target);

            float size = GetHeight();

            glDisable(GL_TEXTURE_2D);

            const Color& colQuad = mCaption.GetColor();
            glColor4ub(colQuad.r, colQuad.g, colQuad.b, colQuad.a);

            glBegin(GL_QUADS);
                glVertex2f(0, 0);
                glVertex2f(0, size);
                glVertex2f(size, size);
                glVertex2f(size, 0);
            glEnd();

            if (!mChecked)
                return;

            const Color& colCheck = GetColor();
            glColor4ub(colCheck.r, colCheck.g, colCheck.b, colCheck.a);

            glBegin(GL_LINES);
                glVertex2f(1.f, 1.f);
                glVertex2f(size - 1.f, size - 1.f);
                glVertex2f(size - 1.f, 1.f);
                glVertex2f(1.f, size - 1.f);
            glEnd();
        }

        void    CheckBox::Render(RenderTarget& target) const
        {
            const Vector2f& absPos = GetAbsolutePosition();

            glEnable(GL_SCISSOR_TEST);
            glScissor(absPos.x, target.GetHeight() - GetHeight() - absPos.y, GetWidth(), GetHeight());

            Widget::Render(target);

            glDisable(GL_SCISSOR_TEST);
        }

    }
}
