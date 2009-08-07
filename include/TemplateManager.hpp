#ifndef TEMPLATEMANAGER_HPP_INCLUDED
#define TEMPLATEMANAGER_HPP_INCLUDED

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

namespace sf
{
    class Color;

    namespace ui
    {
        typedef std::map<std::string, std::string> TemplateProperties;
        typedef std::map<std::string, TemplateProperties> Templates;

        class TemplateManager
        {
            public :

                static TemplateManager*     Get();
                static void                 Kill();

                TemplateProperties&         GetTemplate(const std::string& name);
                bool                        AddTemplatesFromFile(const std::string& filename);

                template<typename T>
                static  T   GetValue(const std::string& value, const T& defaultValue)
                {
                    T   retValue;

                    std::istringstream iss(value);
                    if (iss >> retValue)
                        return retValue;
                    return (retValue = defaultValue);
                }

                static Color GetColorValue(const std::string& value, const Color& defaultValue);

            private :
                TemplateManager();
                ~TemplateManager();

                static  TemplateManager*    mInstance;
                Templates                   mTemplates;
        };
    }
}

#endif // TEMPLATEMANAGER_HPP_INCLUDED
