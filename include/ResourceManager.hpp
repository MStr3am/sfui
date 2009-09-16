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

#include <string>
#include <map>

#include <sstream>
#include <SFML/Graphics/Rect.hpp>
#include "Area.hpp"

namespace sf
{
    class Color;
    class Font;
    class Image;
    class Sprite;

    namespace ui
    {
        typedef std::map<std::string, std::string>          StyleProperties;
        typedef std::map<std::string, StyleProperties>      Styles;

        typedef std::map<std::string, Font*>                Fonts;
        typedef std::map<std::string, Image*>               Images;

        class ResourceManager
        {
            public :

                static ResourceManager*     Get();
                static void                 Kill();

                StyleProperties&            GetStyle(const std::string& name);
                bool                        AddStylesFromFile(const std::string& filename);


                mutable Area                WidgetArea;

                template<typename T>
                T           GetValue(const std::string& value, const T& defaultValue)
                {
                    T   retValue;

                    std::istringstream iss(value);
                    if (iss >> retValue)
                        return retValue;
                    return (retValue = defaultValue);
                }

                Color                       GetColorValue(const std::string& value, const Color& defaultValue);

                Font*                       GetFont(const std::string& filename, float size = 30.f);
                Sprite                      GetImage(const std::string& name);

            private :
                ResourceManager();
                ~ResourceManager();

                bool                        LoadFont(const std::string& resId, const std::string& filename, float size = 30.f);
                bool                        LoadImage(const std::string& resId, const std::string& filename);

                static  ResourceManager*    mInstance;

                /* --- Resources --- */
                Styles                      mStyles;
                Fonts                       mFonts;
                Images                      mImages;


        };
    }
}

#endif // RESOURCEMANAGER_HPP_INCLUDED
