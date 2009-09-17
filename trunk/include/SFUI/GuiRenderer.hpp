#ifndef GUIRENDERER_HPP_INCLUDED
#define GUIRENDERER_HPP_INCLUDED

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

/** \file GuiRenderer.hpp
 * \brief The GUI engine class.
 * \author Robin Ruaux
 */

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFUI/Widget.hpp>

namespace sf
{
    namespace ui
    {
        typedef     Vector2<unsigned int>   Vector2ui;

        /** \class GuiRenderer
         *
         * \brief The GUI engine class.
         */
        class GuiRenderer
        {
            public:

                /** \brief Constructor
                 *
                 * Constructor of GuiRenderer class.
                 *
                 * \param renderWindow Needs a reference to the sf::RenderWindow.
                 */
                GuiRenderer(RenderWindow& renderWindow);

                /** \brief Destructor
                 *
                 * Destructor of GuiRenderer class.
                 */
                ~GuiRenderer();

                /** \brief Inject a new event to the gui system.
                 *
                 * \param event The event to be injected.
                 */
                virtual void        InjectEvent(const Event& event);

                /** \brief Resize the gui view.
                 *
                 * \param size The new size of the view.
                 */
                void                Resize(const Vector2ui& size);

                /** \brief Resize the gui view.
                 *
                 * \param width The new width of the view.
                 * \param height The new height of the view.
                 */
                void                Resize(unsigned int width, unsigned int height);

                /** \brief Display the widget hierarchy.
                 *
                 */
                virtual void        Display();

                /** \brief Get the top widget container.
                 *
                 * \return The gui top widget.
                 */
                Widget&             GetTopWidget();

                /** \brief Set the widget to be focused.
                 *
                 * \param widget The widget to be focused.
                 */
                void                SetFocusedWidget(Widget* widget);

                /** \brief Get the focused widget.
                 *
                 * \return The focused widget (0 if no one has the focus)
                 */
                Widget*             GetFocusedWidget() const;

                /** \brief Get the hovered widget.
                 *
                 * \return The hovered widget (0 if no one has been hovered)
                 */
                Widget*             GetHoveredWidget() const;

            protected:
                void                HandleFocus();

                View                mView;

            private:

                void                SetHoveredWidget(Widget* widget, const Vector2ui& mouse, Vector2f initialPosition);

                RenderWindow&       mRenderWindow;

                Widget              mTopWidget;

                bool                mMouseInside;
        };

    }

}

#endif // GUIRENDERER_HPP_INCLUDED
