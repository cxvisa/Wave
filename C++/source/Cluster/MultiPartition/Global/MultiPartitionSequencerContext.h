/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONSEQUENCERCONTEXT_H
#define MULTIPARTITIONSEQUENCERCONTEXT_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Cluster/MultiPartition/Global/WavePartitionManagedObject.h"

namespace WaveNs
{

class MultiPartitionSynchronousLinearSequencerContext : public PrismSynchronousLinearSequencerContext
{
    private:
    protected:
    public:
                 MultiPartitionSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~MultiPartitionSynchronousLinearSequencerContext (void); 

        void     setWavePartitionManagedObject(WavePartitionManagedObject *pObject);
        WavePartitionManagedObject *getWavePartitionManagedObject(void);
        ObjectId                 getWaveNodeObjectId(void);
        void                     setWaveNodeObjectId(const ObjectId &objId);
    // Now the data members
    private:
             WavePartitionManagedObject   *m_pWavePartitionManagedObject;
             ObjectId                   m_waveNodeObjectId;
    protected:
    public:
};

}

#endif // MULTIPARTITIONSEQUENCERCONTEXT_H
