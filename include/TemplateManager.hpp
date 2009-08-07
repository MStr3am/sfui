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
    namespace ui
    {
        typedef std::map<std::string, std::string> TemplateProperties;
        typedef std::map<std::string, TemplateProperties> Templates;

        class TemplateManager
        {
            public :

                enum Type
                {
                    NUMBER,
                    STRING,
                    RGB_COLOR,
                    HEX_COLOR
                };

                static TemplateManager*     Get();
                static void                 Kill();

                TemplateProperties&         GetTemplate(const std::string& name);
                bool                        AddTemplatesFromFile(const std::string& filename);

                template<typename T>
                static  T   GetValue(enum Type convert, const std::string& value, const T& defaultValue)
                {
                    T   retValue;

                    if (convert == STRING || convert == NUMBER)
                    {
                        std::istringstream iss(value);
                        if (iss >> retValue)
                            return retValue;
                    }
                    else if (convert == RGB_COLOR || convert == HEX_COLOR)
                    {
                        // TODO
                    }
                    return (retValue = defaultValue);
                }

            private :
                TemplateManager();
                ~TemplateManager();

                static  TemplateManager*    mInstance;
                Templates                   mTemplates;
        };
    }
}

#endif // TEMPLATEMANAGER_HPP_INCLUDED
