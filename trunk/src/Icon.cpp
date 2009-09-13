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

#include "Icon.hpp"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{
    namespace ui
    {
        Icon::Icon()
            :   Widget(),
                mSprite()
        {
            SetDefaultStyle("BI_Icon");
            LoadStyle(GetDefaultStyle());
        }

        void    Icon::LoadStyle(const std::string& nameStyle)
        {
            Widget::LoadStyle(nameStyle);

            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            if (properties["image"] != "")
            {
                mSprite = rm->GetImage(properties["image"]);

                const Image* img = mSprite.GetImage();

                if (img && (properties["width"] == "" || properties["height"] == ""))
                {
                    SetSize((properties["width"] == "") ? img->GetWidth() : GetWidth(),
                            (properties["height"] == "") ? img->GetHeight() : GetHeight());
                }
                else
                {
                    mSprite.Resize(GetWidth(), GetHeight());
                }
            }
        }

        void    Icon::SetImage(const Image& image, bool resize)
        {
            mSprite.SetImage(image);

            if (resize)
            {
                SetSize(image.GetWidth(), image.GetHeight());
            }
            else
            {
                mSprite.Resize(GetWidth(), GetHeight());
            }
        }

        const Image*   Icon::GetImage() const
        {
            return mSprite.GetImage();
        }

        void    Icon::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mSprite.Resize(GetSize());
            }
        }

        void    Icon::OnPaint(RenderTarget& target) const
        {
            Widget::OnPaint(target);

            if (mSprite.GetImage())
                target.Draw(mSprite);
        }

    }
}
