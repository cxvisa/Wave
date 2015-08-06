/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERTESTCONTEXTS_H
#define CLUSTERTESTCONTEXTS_H

#include "Framework/Utils/WaveLinearSequencerContext.h"


namespace WaveNs
{

class ClusterTestContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
            ClusterTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
           ~ClusterTestContext ();

        UI32  getNumberOfFailures                ();
        void  setNumberOfFailures                (UI32 numberOfFailures);
        void  incrementNumberOfFailures          ();
        void  incrementNumberOfFailures          (UI32 numberOfFailures);

    // Now the data members

    private :
        UI32 m_numberOfFailures;

    protected :
    public :
};

}

#endif // CLUSTERTESTCONTEXTS_H
