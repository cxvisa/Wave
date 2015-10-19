/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGSYNCHRONOUSLINEARSEQUENCERCONTEXT_H
#define DISTRIBUTEDLOGSYNCHRONOUSLINEARSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"

namespace WaveNs
{

class DistributedLogSynchronousLinearSequencerContext : public WaveSynchronousLinearSequencerContext
{
    private:
    protected:
    public:
                            DistributedLogSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                            DistributedLogSynchronousLinearSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual            ~DistributedLogSynchronousLinearSequencerContext (); 

                UI64        getNumberOfLogEntries                           () const;
                void        setNumberOfLogEntries                           (const UI64 &numberOfLogEntries);
        
    // Now the data members
    private:
        UI64    m_numberOfLogEntries;

    protected:
    public:
};

}

#endif // DISTRIBUTEDLOGSYNCHRONOUSLINEARSEQUENCERCONTEXT_H
