/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEPRIMARYUNCONTROLLEDFAILOVERAGENT_H
#define WAVEPRIMARYUNCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/WaveFailoverAgent.h"

namespace WaveNs
{

class WavePrimaryUncontrolledFailoverAgent : public WaveFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         WavePrimaryUncontrolledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~WavePrimaryUncontrolledFailoverAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEPRIMARYUNCONTROLLEDFAILOVERAGENT_H
