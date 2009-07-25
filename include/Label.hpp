#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

/*
    This file is part of ReGen (by Robin RUAUX).

    ReGen is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ReGen is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ReGen.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Widget.hpp"
#include <SFML/Graphics/String.hpp>

namespace sf
{
    class Label : public Widget
    {
        public :
            Label(const Unicode::Text& caption, float textSize = 15.f);

        protected :
            virtual void    OnPaint(RenderTarget& target) const;
            virtual void    OnChange(Widget::Property property);

        private :
            String          mCaption;

    };


}

#endif // LABEL_HPP_INCLUDED
