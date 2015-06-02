/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTOPERATION_H
#define WAVEMANAGEDOBJECTOPERATION_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveManagedObjectOperation
{
    private :
    protected :
    public :
                        WaveManagedObjectOperation ();
                        ~WaveManagedObjectOperation ();

        void            setReason                   (const ResourceId &reason);
        ResourceId      getReason                   () const;

    // Now the data members

    private :
        ResourceId  m_reason;

    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTOPERATION_H
