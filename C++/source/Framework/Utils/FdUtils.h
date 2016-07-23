/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FDUTILS_H
#define FDUTILS_H

#include "Framework/Types/Types.h"

#include <sys/select.h>

namespace WaveNs
{

class FdUtils
{
    private :
    protected :
    public :
        static void fdCopy                  (fd_set *pSource, fd_set *pDestination);
        static SI32 fdMax                   (fd_set *pSource);
        static SI32 fdCount                 (fd_set *pSource);
        static bool getNumberOfAvailableFds (UI32 &numberOfAvailableFds);

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // FDUTILS_H
