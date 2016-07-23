/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/FdUtils.h"

namespace WaveNs
{

void FdUtils::fdCopy (fd_set *pSource, fd_set *pDestination)
{
    SI32 i = 0;

    FD_ZERO (pDestination);

    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, pSource))
        {
            FD_SET (i, pDestination);
        }
    }
}

SI32 FdUtils::fdMax (fd_set *pSource)
{
    SI32 i = 0;

    for (i = FD_SETSIZE - 1; i >= 0; i--)
    {
        if (FD_ISSET(i, pSource))
        {
            return (i);
        }
    }

    return (-1);
}

SI32 FdUtils::fdCount (fd_set *pSource)
{
    SI32 i     = 0;
    SI32 count = 0;

    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (FD_ISSET(i, pSource))
        {
            count++;
        }
    }

    return (count);
}

}
