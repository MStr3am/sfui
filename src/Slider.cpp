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

#include <SFUI/Slider.hpp>

#include <iostream>

namespace sf
{
    namespace ui
    {
        Slider::Slider(SliderType type)
            :   Widget(),
                mSliderType(type),
                mDecorator(),
                mSlider(),
                mSliderMovablePolicy(mSlider),
                mMinValue(0), mMaxValue(100), mValue(0)
        {
            mSliderMovablePolicy.SetBlocked(true);
            mSliderMovablePolicy.SetMovable(false);

            if (mSliderType == HORIZONTAL)
            {
                SetDefaultStyle("BI_HSlider");
                mSliderMovablePolicy.SetMovableX(true);
            }
            else if (mSliderType == VERTICAL)
            {
                SetDefaultStyle("BI_VSlider");
                mSliderMovablePolicy.SetMovableY(true);
            }

            LoadStyle(GetDefaultStyle());

            Add(&mDecorator);
            Add(&mSlider);

            mSlider.AddMouseListener(this);

            SetValue(GetMinValue());
        }

        void    Slider::OnMouseMoved(const Event::MouseMoveEvent& mouse)
        {
            float factor = 0.f;

            if (mSliderType == HORIZONTAL)
            {
                factor = (mMaxValue - mMinValue) / (GetWidth() - mSlider.GetWidth());
                mValue = mSlider.GetPosition().x * factor;
                mSlider.SetX(mValue / factor);
            }
            else if (mSliderType == VERTICAL)
            {
                factor = (mMaxValue - mMinValue) / (GetHeight() - mSlider.GetHeight());
                mValue = mSlider.GetPosition().y * factor;
                mSlider.SetY(mValue / factor);
            }
        }

        void    Slider::LoadStyle(const std::string& style)
        {
            mDecorator.LoadStyle(style + "->Background");

            mSlider.LoadStyle(style + "->Slider");
            mSlider.SetFocusable(true);

            Widget::LoadStyle(style);
        }

        void    Slider::SetMinValue(Uint16 minValue)
        {
            if (minValue < mMaxValue)
                mMinValue = minValue;
        }

        void    Slider::SetMaxValue(Uint16 maxValue)
        {
            if (maxValue > mMinValue)
                mMaxValue = maxValue;
        }

        void    Slider::SetValue(Uint16 value)
        {
            if (value <= mMaxValue && value >= mMinValue)
            {
                mValue = value;
                if (mSliderType == HORIZONTAL)
                    mSlider.SetX(mValue / ((mMaxValue - mMinValue) / (GetWidth() - mSlider.GetWidth())));
                else if (mSliderType == VERTICAL)
                    mSlider.SetY(mValue / ((mMaxValue - mMinValue) / (GetHeight() - mSlider.GetHeight())));
            }
        }

        Uint16  Slider::GetValue() const
        {
            return mValue;
        }

        Uint16  Slider::GetMinValue() const
        {
            return mMinValue;
        }

        Uint16  Slider::GetMaxValue() const
        {
            return mMaxValue;
        }

    }
}
