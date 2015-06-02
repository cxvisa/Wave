/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveLocalManagedObject.h"
#include "Cluster/Local/WaveSlotLocalManagedObject.h"

namespace WaveNs
{

WaveLocalManagedObject::WaveLocalManagedObject (WaveObjectManager *pWaveObjectManager)
    : PrismElement               (pWaveObjectManager),
      PrismPersistableObject     (WaveLocalManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject          (pWaveObjectManager),
      WaveLocalManagedObjectBase (this)
{
}

WaveLocalManagedObject::~WaveLocalManagedObject ()
{
}

string WaveLocalManagedObject::getClassName ()
{
    return ("WaveLocalManagedObject");
}

void WaveLocalManagedObject::addWaveSlotLMOObjectId (const ObjectId &waveSlotObjectId)
{
    m_waveSlotLMOObjectIds.push_back (waveSlotObjectId);
}
vector<ObjectId> WaveLocalManagedObject::getWaveSlotLMOObjectIds ()
{
    return m_waveSlotLMOObjectIds;
}
ResourceId WaveLocalManagedObject::removeWaveSlotLMOObjectId (const ObjectId &waveSlotLMOObjectId)
{
    vector<ObjectId>::iterator waveSlotLMOElementIter = m_waveSlotLMOObjectIds.begin ();
    vector<ObjectId>::iterator waveSlotLMOElementLast = m_waveSlotLMOObjectIds.end ();
    bool OidFound = false;

    while (waveSlotLMOElementIter != waveSlotLMOElementLast)
    {
        if ((*waveSlotLMOElementIter) == waveSlotLMOObjectId)
        {
            OidFound = true;
            break;
        }
        ++waveSlotLMOElementIter;
    }
    if (OidFound)
    {
        m_waveSlotLMOObjectIds.erase (waveSlotLMOElementIter);
        return FRAMEWORK_SUCCESS;
    }
    else
    {
        trace (TRACE_LEVEL_ERROR,"WaveLocalManagedObject::removeWaveSlotLMOObjectId: Remove waveSlotLMO ObjectId not found");
        return FRAMEWORK_ERROR;
    }

}

void WaveLocalManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
    

    WaveLocalManagedObjectBase::setupAttributesForPersistence ();
}

void WaveLocalManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();
    

    WaveLocalManagedObjectBase::setupAttributesForCreate ();
}

}
