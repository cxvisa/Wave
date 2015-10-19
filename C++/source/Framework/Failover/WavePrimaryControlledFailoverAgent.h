/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEPRIMARYCONTROLLEDFAILOVERAGENT_H
#define WAVEPRIMARYCONTROLLEDFAILOVERAGENT_H

#include "Framework/Failover/WaveFailoverAgent.h"

namespace WaveNs
{

class WavePrimaryControlledFailoverAgent : public WaveFailoverAgent
{
    private :
        virtual FrameworkObjectManagerFailoverReason getFailoverReason () const;
        virtual WaveBootReason                       getBootReason     () const;

    protected :
    public :
         WavePrimaryControlledFailoverAgent (WaveObjectManager *pWaveObjectManager, FrameworkSequenceGenerator &currentFrameworkSequenceGenerator);
        ~WavePrimaryControlledFailoverAgent ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEPRIMARYCONTROLLEDFAILOVERAGENT_H
