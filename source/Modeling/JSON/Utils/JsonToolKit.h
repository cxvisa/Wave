/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONTOOLKIT_H
#define JSONTOOLKIT_H

#include "Framework/Types/Types.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class JsonToolKit
{
    private :
    protected :
    public :
        static bool splitJsonValueString (const string &input, vector<string> &jsonValueStrings);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // JSONTOOLKIT_H
