/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef BASE64UTILS_H
#define BASE64UTILS_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class Base64Utils
{
    private :
    protected:
    public :
        static string encode (const string &input);
        static string decode (const string &input);

    // Now the data members

    private :
    protected:
    public :
};

}

#endif // BASE64UTILS_H
