#ifndef POLICY_HPP_INCLUDED
#define POLICY_HPP_INCLUDED

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

/** \file Policy.hpp
 * \brief Basic policy class.
 * \author Robin Ruaux
 */

#include <SFUI/Widget.hpp>

#include <SFUI/MouseListener.hpp>
#include <SFUI/KeyListener.hpp>

#include <SFML/System/Unicode.hpp>

namespace sf
{
    namespace ui
    {
        /** \class Policy
         *
         * \brief Basic policy class for widgets
         */
        class Policy : public MouseListener, public KeyListener
        {
            public :

                /** \brief Constructor.
                 *
                 * Constructor of Policy class.
                 *
                 * \param widget Attached widget to the policy.
                 * \param name Policy name.
                 */
                Policy(Widget& widget, const Unicode::Text& name)
                    :   mWidget(widget),
                        mName(name)
                {
                    mWidget.AddMouseListener(this);
                    mWidget.AddKeyListener(this);
                }

                /** \brief Destructor.
                 *
                 * Destructor of Policy class
                 */
                ~Policy()
                {
                    mWidget.RemoveMouseListener(this);
                    mWidget.RemoveKeyListener(this);
                }

                /** \brief Get the policy name.
                 *
                 * \return The policy name.
                 */
                const Unicode::Text&    GetName()
                {
                    return mName;
                }

                /** \brief Load a new style for the policy.
                 *
                 * This method is virtual and could be reimplemented by other policies to load properties.
                 * \param styleName The style name value to load.
                 */
                virtual void            LoadStyle(const std::string& styleName) {};

            protected :

                Widget&                 mWidget;

            private :

                Unicode::Text           mName;
        };
    }
}

#endif // POLICY_HPP_INCLUDED
