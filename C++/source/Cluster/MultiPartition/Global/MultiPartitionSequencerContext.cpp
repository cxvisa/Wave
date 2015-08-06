/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#include "Cluster/MultiPartition/Global/MultiPartitionSequencerContext.h"

namespace WaveNs
{

MultiPartitionSynchronousLinearSequencerContext::MultiPartitionSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pWavePartitionManagedObject(NULL)
{
        // Do nothing.
}

MultiPartitionSynchronousLinearSequencerContext::~MultiPartitionSynchronousLinearSequencerContext ()
{
        // Do nothing.
}

WavePartitionManagedObject  *MultiPartitionSynchronousLinearSequencerContext::getWavePartitionManagedObject(void)
{
    return m_pWavePartitionManagedObject;
}


void MultiPartitionSynchronousLinearSequencerContext::setWavePartitionManagedObject(WavePartitionManagedObject *pWavePartitionManagedObject)
{
    m_pWavePartitionManagedObject = pWavePartitionManagedObject;
}

ObjectId  MultiPartitionSynchronousLinearSequencerContext::getWaveNodeObjectId(void)
{
    return m_waveNodeObjectId; 
}

void MultiPartitionSynchronousLinearSequencerContext::setWaveNodeObjectId(const ObjectId &objId)
{
    m_waveNodeObjectId = objId;
}



}
