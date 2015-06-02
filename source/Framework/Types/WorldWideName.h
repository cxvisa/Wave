/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WORLDWIDENAME_H
#define WORLDWIDENAME_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class WorldWideName
{
    private :
        static bool isAValidHexaDecimalCharacter (const char &ch);

    protected :
    public :
                       WorldWideName              ();
                       WorldWideName              (const UI8 worldWideName[8]);
                       WorldWideName              (const string &worldWideNameInStringFormat);
                       WorldWideName              (const WorldWideName &worldWideName);
                      ~WorldWideName              ();
                                                  
        string         toString                   ()                                           const;
        void           fromString                 (const string &worldWideNameInStringFormat);
        static bool    isValidWorldWideNameString (const string &worldWideNameInStringFormat);
        UI8           &operator []                (const UI32 &i)                              const;
        bool           operator ==                (const WorldWideName &worldWideName)         const;
        bool           operator !=                (const WorldWideName &worldWideName)         const;
        WorldWideName &operator =                 (const WorldWideName &worldWideName);
        void           setSeparator               (const char &separator);
        char           getSeparator               ()                                           const;
        ResourceId     loadFromPlainString        (const string &worldWideNameInPlainStringFormat);
    // Now the data members

    private :
                     UI8  *m_pName;
        static const UI32  m_nameLength = 8;
                     char  m_separator;

    protected :
    public :
};

}

#endif // WORLDWIDENAME_H
