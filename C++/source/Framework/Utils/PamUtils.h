/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PAMUTILS_H
#define PAMUTILS_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class PamUtils
{
    private :
    protected :
    public :
        static bool authenticate (const string &authenticationService, const string& userName, const string &password);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PAMUTILS_H
