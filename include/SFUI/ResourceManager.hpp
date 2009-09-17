#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

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

/** \file ResourceManager.hpp
 * \brief Utility class for managing widget resources.
 * \author Robin Ruaux
 */

#include <string>
#include <map>
#include <sstream>

#include <SFML/Graphics/Rect.hpp>

#include <SFUI/Area.hpp>

namespace sf
{
    class Color;
    class Font;
    class Image;
    class Sprite;

    namespace ui
    {
        /** \typedef std::map<std::string, std::string> StyleProperties
         *
         * Widget style properties with syntax property["name"] = "value".
         */
        typedef std::map<std::string, std::string>          StyleProperties;

        /** \typedef std::map<std::string, StyleProperties> Styles
         *
         * Container for Style resources.
         */
        typedef std::map<std::string, StyleProperties>      Styles;

        /** typedef std::map<std::string, Font*> Fonts;
         *
         * Container for Font resources.
         */
        typedef std::map<std::string, Font*>                Fonts;

        /** typedef std::map<std::string, Image*> Images;
         *
         * Container for Image resources.
         */
        typedef std::map<std::string, Image*>               Images;

        /** \class ResourceManager
         *
         * \brief Utility class for managing widget resources.
         */
        class ResourceManager
        {
            public :

                /** \brief Get the ResourceManager instance.
                 *
                 * \return The ResourceManager unique instance.
                 */
                static ResourceManager*     Get();

                /** \brief Kill the ResourceManager instance.
                 *
                 * When the singleton is killed, all resources are destroyed.
                 * By default, the GuiRenderer kills it properly.
                 */
                static void                 Kill();

                /** \brief Get a style from memory.
                 *
                 * \param name The style name to load.
                 * \return The wanted named style.
                 */
                StyleProperties&            GetStyle(const std::string& name);

                /** \brief Add new styles and resources from an xml file.
                 *
                 * \param filename The name of the file to load.
                 * \return true if file has been successfuly loaded.
                 * \return false otherwise.
                 */
                bool                        AddStylesFromFile(const std::string& filename);

                mutable Area                WidgetArea;

                /** \brief Get a property value from its string value.
                 *
                 * \param value The property value to be converted.
                 * \param defaultValue The property value to be returned if conversion failed.
                 * \return The property value.
                 */
                template<typename T>
                T           GetValue(const std::string& value, const T& defaultValue)
                {
                    T   retValue;

                    std::istringstream iss(value);
                    if (iss >> retValue)
                        return retValue;
                    return (retValue = defaultValue);
                }

                /** \brief Get a property color value from its string value.
                 *
                 * Color string value could be represented as different syntaxes :
                 * <ul>
                 * <li>hexadecimal : "#FF0000" , "#cfEfAA"</li>
                 * <li>rgb color : "rgb: 123, 244, 234" , "rgb:   0 ,0,  0"</li>
                 * <li>rgb + alpha color : "rgba: 244, 123, 45, 34" </li>
                 * </ul>
                 *
                 * \param value The property string value to be parsed.
                 * \param defaultValue The color to be applied if parsing failed.
                 * \return The property color.
                 */
                Color                       GetColorValue(const std::string& value, const Color& defaultValue);

                /** \brief Get a property font value from its string value.
                 *
                 * The string value represents
                 * <ul>
                 * <li>a font file : "data/my_font.ttf"</li>
                 * <li>a resource alias defined like this :
                 * \code
                 <resources>
                    <font name="MyAlias" src="data/my_font.ttf" size="23" />
                 </resources>
                 * \endcode </li></ul>
                 *
                 * \param filename The font string value.
                 * \param size The font size.
                 * \return The loaded font (0 if failed).
                 */
                Font*                       GetFont(const std::string& filename, float size = 30.f);

                /** \brief Get an image from its string value
                 *
                 * The string value represents
                 * <ul>
                 * <li>an image : "data/my_image.png"</li>
                 * <li>a subpart of an image : "sub: data/my_image.png , 0 , 0, 15, 15" (4 last arguments are the the sf::IntRect pixel selection)</li>
                 * <li>a resource alias defined like this :
                 * \code
                 <resources>
                    <image name="MyAlias" src="data/my_image.png" />
                 </resources>
                 * \endcode </li></ul>
                 *
                 * \param name The image string value.
                 * \return A sprite of the loaded image.
                 */
                Sprite                      GetImage(const std::string& name);

            private :

                ResourceManager();

                ~ResourceManager();

                bool                        LoadFont(const std::string& resId, const std::string& filename, float size = 30.f);

                bool                        LoadImage(const std::string& resId, const std::string& filename);

                static  ResourceManager*    mInstance;

                Styles                      mStyles;

                Fonts                       mFonts;

                Images                      mImages;

        };
    }
}

#endif // RESOURCEMANAGER_HPP_INCLUDED
