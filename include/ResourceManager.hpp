#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

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

#include <string>
#include <map>

#include <sstream>
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
    class Color;
    class Font;
    class Image;
    class Sprite;

    namespace ui
    {
        typedef std::map<std::string, std::string> TemplateProperties;
        typedef std::map<std::string, TemplateProperties> Templates;

        typedef std::map<std::string, Font*>         Fonts;
        typedef std::map<std::string, Image*>        Images;

        class ResourceManager
        {
            public :

                static ResourceManager*     Get();
                static void                 Kill();

                TemplateProperties&         GetTemplate(const std::string& name);
                bool                        AddTemplatesFromFile(const std::string& filename);

                template<typename T>
                T           GetValue(const std::string& value, const T& defaultValue)
                {
                    T   retValue;

                    std::istringstream iss(value);
                    if (iss >> retValue)
                        return retValue;
                    return (retValue = defaultValue);
                }

                Color       GetColorValue(const std::string& value, const Color& defaultValue);

                Font*       GetFont(const std::string& filename, float size = 30.f);
                Image*      GetImage(const std::string& filename);
                Sprite      GetSubImage(const std::string& filename, const IntRect& subRect);

            private :
                ResourceManager();
                ~ResourceManager();

                static  ResourceManager*    mInstance;

                /* --- Resources --- */
                Templates                   mTemplates;
                Fonts                       mFonts;
                Images                      mImages;
        };
    }
}

#endif // RESOURCEMANAGER_HPP_INCLUDED
