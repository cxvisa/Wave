/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTIMERTESTCONTEXTS_H
#define FRAMEWORKTIMERTESTCONTEXTS_H

#include "Framework/Utils/WaveLinearSequencerContext.h"


namespace WaveNs
{

class FrameworkTimerTestContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
            FrameworkTimerTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
           ~FrameworkTimerTestContext ();

        UI32  getNumberOfFailures                ();
        void  setNumberOfFailures                (UI32 numberOfFailures);
        void incrementNumberOfFailures           ();
        void incrementNumberOfFailures           (UI32 numberOfFailures);

    // Now the data members

    private :
        UI32 m_numberOfFailures;

    protected :
    public :
};

}

#endif // FRAMEWORKTIMERTESTCONTEXTS_H
