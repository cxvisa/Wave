/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERDELETECONTEXT_H
#define CLUSTERDELETECONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class PrismCluster;
class WaveManagedObject;

class ClusterDeleteContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                                     ClusterDeleteContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                     ClusterDeleteContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                    ~ClusterDeleteContext ();

        PrismCluster                *getPPrismCluster     () const;
        void                         setPPrismCluster     (PrismCluster *pPrismCluster);
        vector<WaveManagedObject *> *getPSecondaryNodes   () const;
        void                         setPSecondaryNodes   (vector<WaveManagedObject *> *pSecondaryNodes);

    // Now the data members

    private :
        PrismCluster                 *m_pPrismCluster;
        vector<WaveManagedObject *>  *m_pSecondaryNodes;

    protected :
    public :
};

typedef ClusterDeleteContext ClusterBootContext;

}

#endif // CLUSTERDELETECONTEXT_H
