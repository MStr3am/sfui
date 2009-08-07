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

#include "TemplateManager.hpp"
#include <tinyxml.h>
#include <iostream>

namespace sf
{
    namespace ui
    {
        TemplateManager* TemplateManager::mInstance = 0;

        TemplateManager* TemplateManager::Get()
        {
            if (!mInstance)
            {
                mInstance = new TemplateManager();
            }
            return mInstance;
        }

        TemplateManager::TemplateManager()
        {

        }

        TemplateManager::~TemplateManager()
        {

        }

        void TemplateManager::Kill()
        {
            delete mInstance;
            mInstance = 0;
        }

        TemplateProperties&   TemplateManager::GetTemplate(const std::string& name)
        {
            return mTemplates[name];
        }

        bool    TemplateManager::AddTemplatesFromFile(const std::string& filename)
        {
            TiXmlDocument file(filename);

            if (!file.LoadFile())
            {
                std::cerr << "Could not load \"" << filename << "\" template file" << std::endl;
                std::cerr << "Reason :" << file.ErrorDesc() << std::endl;
                return false;
            }

            TiXmlHandle hdlAll(&file);
            TiXmlElement *t = hdlAll.FirstChildElement().Element();

            if (!t)
            {
                std::cerr << "Unable to parse template file" << std::endl;
                return false;
            }

            while (t)
            {
                TemplateProperties  properties;

                const std::string& nameTpl = t->Attribute("name");

                TiXmlHandle hdlTpl(t);
                TiXmlElement *p = hdlTpl.FirstChildElement().Element();

                while (p)
                {
                    properties[p->Attribute("name")] = p->Attribute("value");
                    p = p->NextSiblingElement();
                }

                mTemplates[nameTpl] = properties;

                t = t->NextSiblingElement();
            }

            return true;

        }

    }
}
