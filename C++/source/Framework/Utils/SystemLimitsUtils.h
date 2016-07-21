/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SYSTEMLIMITSUTILS_H
#define SYSTEMLIMITSUTILS_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class SystemLimitsUtils
{
    private :
    protected :
    public :

        static bool getMaxNumberOfOpenFiles          (UI32 &softLimit, UI32 &hardLimit);
        static bool getFileDescriptorsCurrentlyInUse (vector<UI32> &fileDescriptorsCurrentlyInUse);

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // SYSTEMLIMITSUTILS_H
