/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESECONDARYUNCONTROLLEDFAILOVERAGENT_H
#define WAVESECONDARYUNCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/WaveFailoverAgent.h"

namespace WaveNs
{

class WaveSecondaryUncontrolledFailoverAgent : public WaveFailoverAgent
{
    private :
        virtual bool                                 isToBeExcludedForFailover (const WaveServiceId &waveServiceId);
        virtual FrameworkObjectManagerFailoverReason getFailoverReason         () const;
        virtual WaveBootReason                       getBootReason             () const;

    protected :
    public :
                            WaveSecondaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
                           ~WaveSecondaryUncontrolledFailoverAgent ();
        virtual void        execute                                 (WaveFailoverAgentContext *pWaveFailoverAgentContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESECONDARYUNCONTROLLEDFAILOVERAGENT_H
