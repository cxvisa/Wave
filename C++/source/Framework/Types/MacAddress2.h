/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Pritee Kadu                                                  *
 ***************************************************************************/

#ifndef MACADDRESS2_H
#define MACADDRESS2_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class MacAddress2
{
    private :
        static bool isAValidHexaDecimalCharacter    (const char &ch);
               UI16 getValueFromChar                (char ch);

    public :
                    MacAddress2              ();
                    MacAddress2              (const UI16 macAddress[3]);
                    MacAddress2              (const string &macAddressInStringFormat);
                    MacAddress2              (const MacAddress2 &macAddress);
                   ~MacAddress2              ();
                                            
        string      toString                 ()                                           const;
        void        fromString               (const string &macAddressInStringFormat);
        ResourceId  loadFromPlainString      (const string &macAddressInStringFormat);
        static bool isValidMacAddress2String (const string &macAddressInStringFormat);
        UI16        &operator []             (const UI32 &i)                              const;
        bool        operator ==              (const MacAddress2 &macAddress)            const;
        bool        operator !=              (const MacAddress2 &macAddress)            const;
        MacAddress2 &operator =              (const MacAddress2 &macAddress);
        void        setSeparator             (const char &separator);
        char        getSeparator             ()                                           const;

    // Now the data members

    private :
                     UI16  *m_pName;
        static const UI32  m_nameLength = 3;
                     char  m_separator;
        static const UI32  m_maxCharInAUnit = 4;

    protected :
    public :
};

}

#endif // MACADDRESS2_H
