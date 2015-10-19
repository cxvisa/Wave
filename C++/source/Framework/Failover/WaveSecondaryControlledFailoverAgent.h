/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESECONDARYCONTROLLEDFAILOVERAGENT_H
#define WAVESECONDARYCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/WaveFailoverAgent.h"

namespace WaveNs
{

class WaveSecondaryControlledFailoverAgent : public WaveFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         WaveSecondaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~WaveSecondaryControlledFailoverAgent ();
         void setFailoverDueToPrimaryRemoval   ();
         bool getFailoverDueToPrimaryRemoval   () const;
         virtual void execute (WaveFailoverAgentContext *pWaveFailoverAgentContext);
         virtual bool isToBeExcludedForFailover (const WaveServiceId &waveServiceId);        


    // Now the data members

    private :
        bool m_failoverDueToPrimaryRemoval;
    protected :
    public :
};

}

#endif // WAVESECONDARYCONTROLLEDFAILOVERAGENT_H
