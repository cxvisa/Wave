/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTIMERTESTCONTEXTS_H
#define FRAMEWORKTIMERTESTCONTEXTS_H

#include "Framework/Utils/PrismLinearSequencerContext.h"


namespace WaveNs
{

class FrameworkTimerTestContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
            FrameworkTimerTestContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
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
