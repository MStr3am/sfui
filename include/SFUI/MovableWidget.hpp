#ifndef MOVABLEWIDGET_HPP_INCLUDED
#define MOVABLEWIDGET_HPP_INCLUDED

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

/** \file MovableWidget.hpp
 * \brief A basic movable widget.
 * \author Robin Ruaux
 */

#include <SFUI/Widget.hpp>
#include <SFUI/MouseListener.hpp>

namespace sf
{
    namespace ui
    {
        /** \class MovableWidget
         *
         * \brief A basic movable widget.
         */
        class MovableWidget : public Widget, public MouseListener
        {
            public :

                /** \brief Constructor.
                 *
                 * Constructor of MovableWidget class.
                 */
                MovableWidget();

                /** \brief Set the widget to be movable.
                 *
                 * \param movable The widget movable property.
                 */
                void            SetMovable(bool movable = true);

                /** \brief Set the widget to be blocked.
                 *
                 * The blocked property allows the widget to be blocked by its parent boundaries.
                 *
                 * \param blocked The widget blocked property.
                 */
                void            SetBlocked(bool blocked = true);

                /** \brief Check if the widget is movable
                 *
                 * \return The widget movable property.
                 */
                bool            IsMovable() const;

                /** \brief Check if the widget can be blocked
                 *
                 * \return The widget blocked property.
                 */
                bool            IsBlocked() const;

                virtual void    LoadStyle(const std::string& nameStyle);

            protected :

                virtual void    OnMousePressed(const Event::MouseButtonEvent& button);

                virtual void    OnMouseReleased(const Event::MouseButtonEvent& button);

                virtual void    OnMouseMoved(const Event::MouseMoveEvent& mouse);

            private :

                bool            mMovable;

                bool            mBlocked;

                bool            mDragged;

                Vector2f        mDragOffset;

                bool            mNeedUpdate;

        };

    }

}

#endif // MOVABLEWIDGET_HPP_INCLUDED
