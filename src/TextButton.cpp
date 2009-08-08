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

#include "TextButton.hpp"
#include <SFML/Window/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{
    namespace ui
    {
        TextButton::TextButton(const Unicode::Text& caption, float size)
            :   Button(),
                mCaption(caption, size)
        {
            Add(&mCaption);

            SetSize(mCaption.GetSize() + Vector2f(18, 10));
            LoadTemplate("BI_TextButton");
        }

        void    TextButton::LoadTemplate(const std::string& nameTpl)
        {
            Widget::LoadTemplate(nameTpl);

            TemplateProperties& properties = TemplateManager::Get()->GetTemplate(nameTpl);

            SetTextSize(TemplateManager::GetValue(properties["textSize"], GetTextSize()));
            SetTextColor(TemplateManager::GetColorValue(properties["textColor"], GetTextColor()));
        }

        void    TextButton::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mCaption.SetPosition((GetWidth() - mCaption.GetSize().x) / 2, (GetHeight() - mCaption.GetSize().y) / 2);
            }
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

            OnChange(Widget::SIZE);
        }

        float   TextButton::GetTextSize() const
        {
            return mCaption.GetTextSize();
        }

        void    TextButton::OnPressed()
        {
            mCaption.Move(2.f, 2.f);
        }

        void    TextButton::OnReleased()
        {
            mCaption.Move(-2.f, -2.f);
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
