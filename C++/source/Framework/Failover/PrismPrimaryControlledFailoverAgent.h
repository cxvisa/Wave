/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMPRIMARYCONTROLLEDFAILOVERAGENT_H
#define PRISMPRIMARYCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

class PrismPrimaryControlledFailoverAgent : public PrismFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         PrismPrimaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~PrismPrimaryControlledFailoverAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMPRIMARYCONTROLLEDFAILOVERAGENT_H
