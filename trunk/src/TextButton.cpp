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
        TextButton::TextButton(const Unicode::Text& caption)
            :   ImageButton(),
                mCaption(caption)
        {
            Add(&mCaption);
            AdjustSize();
        }

        void    TextButton::LoadTemplate(const std::string& nameTpl)
        {
            ImageButton::LoadTemplate(nameTpl);

            ResourceManager* rm = ResourceManager::Get();
            TemplateProperties& properties = rm->GetTemplate(nameTpl);

            SetTextSize(rm->GetValue(properties["textSize"], GetTextSize()));
            SetTextColor(rm->GetColorValue(properties["textColor"], GetTextColor()));
        }

        void    TextButton::AdjustSize()
        {
            mCaption.SetPosition((GetWidth() - mCaption.GetSize().x) / 2, (GetHeight() - mCaption.GetSize().y) / 2);
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
            AdjustSize();
        }

        float   TextButton::GetTextSize() const
        {
            return mCaption.GetTextSize();
        }

        void    TextButton::OnPressed()
        {
            ImageButton::OnPressed();
            mCaption.Move(1.f, 1.f);
        }

        void    TextButton::OnReleased()
        {
            ImageButton::OnReleased();
            mCaption.Move(-1.f, -1.f);
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
