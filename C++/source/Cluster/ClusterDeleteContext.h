/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERDELETECONTEXT_H
#define CLUSTERDELETECONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveCluster;
class WaveManagedObject;

class ClusterDeleteContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                     ClusterDeleteContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                     ClusterDeleteContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                    ~ClusterDeleteContext ();

        WaveCluster                *getPWaveCluster     () const;
        void                         setPWaveCluster     (WaveCluster *pWaveCluster);
        vector<WaveManagedObject *> *getPSecondaryNodes   () const;
        void                         setPSecondaryNodes   (vector<WaveManagedObject *> *pSecondaryNodes);

    // Now the data members

    private :
        WaveCluster                 *m_pWaveCluster;
        vector<WaveManagedObject *>  *m_pSecondaryNodes;

    protected :
    public :
};

typedef ClusterDeleteContext ClusterBootContext;

}

#endif // CLUSTERDELETECONTEXT_H
