#ifndef TEXTINPUT_HPP_INCLUDED
#define TEXTINPUT_HPP_INCLUDED

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
#include "KeyListener.hpp"
#include "MouseListener.hpp"

namespace sf
{
    namespace ui
    {
        class TextInput : public Widget, public KeyListener, public MouseListener
        {
            public :
                TextInput(const Unicode::Text& text = std::wstring(L"", 255));

                void                        SetText(const Unicode::Text& text);
                const Unicode::Text&        GetText() const;

                void                        SetMaxLength(unsigned int maxLength);
                unsigned int                GetMaxLength() const;

                Unicode::Text               GetSelection() const;

            protected :

                // Inherited from Widget
                virtual void                OnChange(Widget::Property property);
                virtual void                Render(RenderTarget& target) const;

                // Inherited from KeyListener
                virtual void                OnKeyPressed(const Event::KeyEvent& key);
                virtual void                OnTextEntered(const Event::TextEvent& text);

                // Inherited from MouseListener
                virtual void                OnMousePressed(const Event::MouseButtonEvent& button);
                virtual void                OnMouseReleased(const Event::MouseButtonEvent& button);
                virtual void                OnMouseMoved(const Event::MouseMoveEvent& mouse);

                static float                mStringOffset;

            private :
                void                        AdjustRect();
                unsigned int                GetCharacterAtPos(float xOffset);

                Label                       mString;
                unsigned int                mMaxLength;
                unsigned int                mCursorPosition;
                int                         mCursorOffset;

                bool                        mSelectionDragged;
                Vector2i                    mSelectionIndexes;

        };



    }

}

#endif // TEXTINPUT_HPP_INCLUDED
