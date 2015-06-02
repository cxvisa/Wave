/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MACADDRESS_H
#define MACADDRESS_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class MacAddress
{
    private :
        static bool isAValidHexaDecimalCharacter (const char &ch);

    protected :
    public :
                    MacAddress              ();
                    MacAddress              (const UI8 macAddress[6]);
                    MacAddress              (const string &macAddressInStringFormat);
                    MacAddress              (const MacAddress &macAddress);
                   ~MacAddress              ();
                                           
        string      toString                ()                                           const;
        string      toString2               ()                                           const;
        void        fromString              (const string &macAddressInStringFormat);
        ResourceId  loadFromPlainString     (const string &macAddressInStringFormat);
        static bool isValidMacAddressString (const string &macAddressInStringFormat);

        UI8        &operator []   (const UI32 &i)                              const;
        bool        operator ==   (const MacAddress &macAddress)            const;
        bool        operator !=   (const MacAddress &macAddress)            const;
        MacAddress &operator =    (const MacAddress &macAddress);
        void        setSeparator  (const char &separator);
        char        getSeparator  ()                                           const;

    // Now the data members

    private :
                     UI8  *m_pName;
        static const UI32  m_nameLength = 6;
                     char  m_separator;

    protected :
    public :
};

}

#endif // MACADDRESS_H
