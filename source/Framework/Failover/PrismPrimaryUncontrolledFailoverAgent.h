/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMPRIMARYUNCONTROLLEDFAILOVERAGENT_H
#define PRISMPRIMARYUNCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

class PrismPrimaryUncontrolledFailoverAgent : public PrismFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         PrismPrimaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~PrismPrimaryUncontrolledFailoverAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMPRIMARYUNCONTROLLEDFAILOVERAGENT_H
