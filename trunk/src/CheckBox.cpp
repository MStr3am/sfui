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
                mChecked(false),
                mCheckButton(),
                mCaption(caption)
        {
            SetDefaultStyle("BI_CheckBox");
            LoadStyle(GetDefaultStyle());

            Add(&mCaption);
            Add(&mCheckButton);

            mCheckButton.AddMouseListener(this);
            AddMouseListener(this);
        }

        void    CheckBox::SetChecked(bool checked)
        {
            mChecked = checked;
        }

        bool    CheckBox::IsChecked() const
        {
            return mChecked;
        }

        void    CheckBox::OnMousePressed(const Event::MouseButtonEvent& mouse)
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

            mCheckButton.LoadStyle(nameStyle + "->Button");
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
