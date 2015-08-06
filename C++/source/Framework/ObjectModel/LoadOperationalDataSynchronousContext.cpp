/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/LoadOperationalDataSynchronousContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

LoadOperationalDataSynchronousContext::LoadOperationalDataSynchronousContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pWaveManagedObject                   (NULL)
{
}

LoadOperationalDataSynchronousContext::LoadOperationalDataSynchronousContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismSynchronousLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_pWaveManagedObject                   (NULL)
{
}

LoadOperationalDataSynchronousContext::~LoadOperationalDataSynchronousContext ()
{
}

ObjectId LoadOperationalDataSynchronousContext::getWaveManagedObjectId () const
{
    return (m_waveManagedObjctId);
}

void LoadOperationalDataSynchronousContext::setWaveManagedObjectId (const ObjectId &waveManagedObjectId)
{
    m_waveManagedObjctId = waveManagedObjectId;
}

vector<string> LoadOperationalDataSynchronousContext::getOperationalDataFields () const
{
    return (m_operationalDataFields);
}

void LoadOperationalDataSynchronousContext::setOperationalDataFields (const vector<string> &operationalDataFields)
{
    m_operationalDataFields = operationalDataFields;
}

WaveManagedObject *LoadOperationalDataSynchronousContext::getPWaveManagedObject () const
{
    return (m_pWaveManagedObject);
}

void LoadOperationalDataSynchronousContext::setPWaveManagedObject (WaveManagedObject *pWaveManagedObject)
{
    m_pWaveManagedObject = pWaveManagedObject;
}

}
