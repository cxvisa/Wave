/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMSECONDARYUNCONTROLLEDFAILOVERAGENT_H
#define PRISMSECONDARYUNCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

class PrismSecondaryUncontrolledFailoverAgent : public PrismFailoverAgent
{
    private :
        virtual bool                                 isToBeExcludedForFailover (const WaveServiceId &prismServiceId);
        virtual FrameworkObjectManagerFailoverReason getFailoverReason         () const;
        virtual WaveBootReason                       getBootReason             () const;

    protected :
    public :
                            PrismSecondaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
                           ~PrismSecondaryUncontrolledFailoverAgent ();
        virtual void        execute                                 (PrismFailoverAgentContext *pPrismFailoverAgentContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMSECONDARYUNCONTROLLEDFAILOVERAGENT_H
