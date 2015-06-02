/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENTDEBUG_H
#define WAVECLIENTDEBUG_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveClientDebug
{
    private :
    protected :
    public :
                      WaveClientDebug ();
                     ~WaveClientDebug ();

        static  UI32  debugConnect    (UI32 argc, vector<string> argv);
        static  UI32  debugClose      (UI32 argc, vector<string> argv);

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // WAVECLIENTDEBUG_H
