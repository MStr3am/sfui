#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

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

/** \file Area.hpp
 * \brief Utility class for widgets clipping
 * \author Robin Ruaux
 */

#include <stack>

namespace sf
{
    namespace ui
    {
        /** \typedef std::stack<FloatRect> Rects
         *
         * Stack of FloatRect areas.
         */
        typedef std::stack<FloatRect>   Rects;


        /** \class Area
         *
         * \brief Utility class for widgets clipping.
         *
         * This class is used by the ResourceManager to stack areas in memory. It helps widgets to be clipped with glScissor test.
         */
        class Area
        {
            public :

                /** \brief Constructor
                 *
                 * Constructor of Area class.
                 */
                Area()
                    :   mRects()
                {}


                /** \brief Get the top of the stack.
                 *
                 * \return The area on the top of the stack.
                 */
                const FloatRect&    GetTopArea() const
                {
                    return mRects.top();
                }

                /** \brief Pop the stack and return the top Area.
                 *
                 * \return The area on the top of the stack.
                 */
                const FloatRect&    PopArea()
                {
                    mRects.pop();
                    return mRects.top();
                }


                /** \brief Push area to the stack.
                 *
                 * \param rect FloatRect area to be stacked.
                 */
                void                    PushArea(const FloatRect& rect)
                {
                    if (mRects.empty())
                    {
                        mRects.push(rect);
                    }
                    else
                    {
                        const FloatRect& topRect = mRects.top();
                        FloatRect newRect = rect;

                        if (newRect.Left < topRect.Left)
                            newRect.Left = topRect.Left;
                        if (newRect.Top < topRect.Top)
                            newRect.Top = topRect.Top;
                        if (newRect.Right > topRect.Right)
                            newRect.Right = topRect.Right;
                        if (newRect.Bottom > topRect.Bottom)
                            newRect.Bottom = topRect.Bottom;

                        mRects.push(newRect);
                    }
                }


            private:

                Rects               mRects;

        };
    }
}

#endif // AREA_HPP_INCLUDED
