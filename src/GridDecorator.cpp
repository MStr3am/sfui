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

#include "GridDecorator.hpp"

namespace sf
{
    namespace ui
    {

        GridDecorator::GridDecorator()
            :   Icon()
        {
            SetDefaultStyle("BI_GridDecorator");
            LoadStyle(GetDefaultStyle());

            for (unsigned int i = Align::TOP_LEFT; i <= Align::BOTTOM_RIGHT; ++i)
                Add(&mIcons[i]);
        }

        void    GridDecorator::UseGrid(bool useGrid)
        {
            mUseGrid = useGrid;

            for (unsigned int i = Align::TOP_LEFT; i <= Align::BOTTOM_RIGHT; ++i)
                mIcons[i].SetVisible(useGrid);
        }

        bool    GridDecorator::IsGridUsed() const
        {
            return mUseGrid;
        }

        void    GridDecorator::LoadStyle(const std::string& nameStyle)
        {
            ResourceManager* rm = ResourceManager::Get();
            StyleProperties& properties = rm->GetStyle(nameStyle);

            UseGrid(rm->GetValue(properties["useGrid"], IsGridUsed()));

            mIcons[Align::TOP_LEFT].LoadStyle(nameStyle + "->topLeft");
            mIcons[Align::TOP_CENTER].LoadStyle(nameStyle + "->topCenter");
            mIcons[Align::TOP_RIGHT].LoadStyle(nameStyle + "->topRight");

            mIcons[Align::LEFT].LoadStyle(nameStyle + "->left");
            mIcons[Align::CENTER].LoadStyle(nameStyle + "->center");
            mIcons[Align::RIGHT].LoadStyle(nameStyle + "->right");

            mIcons[Align::BOTTOM_LEFT].LoadStyle(nameStyle + "->bottomLeft");
            mIcons[Align::BOTTOM_CENTER].LoadStyle(nameStyle + "->bottomCenter");
            mIcons[Align::BOTTOM_RIGHT].LoadStyle(nameStyle + "->bottomRight");

            Icon::LoadStyle(nameStyle);
        }

        void    GridDecorator::OnChange(Widget::Property property)
        {
            if (property == Widget::SIZE)
            {
                mIcons[Align::TOP_CENTER].SetWidth(GetWidth() - (mIcons[Align::TOP_LEFT].GetWidth() + mIcons[Align::TOP_RIGHT].GetWidth()));
                mIcons[Align::CENTER].SetWidth(GetWidth() - (mIcons[Align::LEFT].GetWidth() + mIcons[Align::RIGHT].GetWidth()));
                mIcons[Align::BOTTOM_CENTER].SetWidth(GetWidth() - (mIcons[Align::BOTTOM_LEFT].GetWidth() + mIcons[Align::BOTTOM_RIGHT].GetWidth()));

                mIcons[Align::LEFT].SetHeight(GetHeight() - (mIcons[Align::TOP_LEFT].GetHeight() + mIcons[Align::BOTTOM_LEFT].GetHeight()));
                mIcons[Align::CENTER].SetHeight(GetHeight() - (mIcons[Align::TOP_CENTER].GetHeight() + mIcons[Align::BOTTOM_CENTER].GetHeight()));
                mIcons[Align::RIGHT].SetHeight(GetHeight() - (mIcons[Align::TOP_RIGHT].GetHeight() + mIcons[Align::BOTTOM_RIGHT].GetHeight()));
            }
            else if (property == Widget::PARENT)
            {
                Widget* parent = GetParent();

                if (parent)
                {
                    SetSize(parent->GetSize());
                    ChangeZIndex(Widget::ALL_BELOW);
                }
            }
            Icon::OnChange(property);
        }
    }
}
