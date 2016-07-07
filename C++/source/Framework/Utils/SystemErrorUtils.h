/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SYSTEMERRORUTILS_H
#define SYSTEMERRORUTILS_H

#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class SystemErrorUtils
{
    private :
    protected :
    public :
        static string getErrorStringForErrorNumber (const SI32 &errorNumber);

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // SYSTEMERRORUTILS_H
