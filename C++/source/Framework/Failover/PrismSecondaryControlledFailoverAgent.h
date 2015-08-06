/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMSECONDARYCONTROLLEDFAILOVERAGENT_H
#define PRISMSECONDARYCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/PrismFailoverAgent.h"

namespace WaveNs
{

class PrismSecondaryControlledFailoverAgent : public PrismFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         PrismSecondaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~PrismSecondaryControlledFailoverAgent ();
         void setFailoverDueToPrimaryRemoval   ();
         bool getFailoverDueToPrimaryRemoval   () const;
         virtual void execute (PrismFailoverAgentContext *pPrismFailoverAgentContext);
         virtual bool isToBeExcludedForFailover (const WaveServiceId &prismServiceId);        


    // Now the data members

    private :
        bool m_failoverDueToPrimaryRemoval;
    protected :
    public :
};

}

#endif // PRISMSECONDARYCONTROLLEDFAILOVERAGENT_H
