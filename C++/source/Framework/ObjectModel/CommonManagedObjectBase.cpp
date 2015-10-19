/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Awanish Kumar Trivedi                                        *
 ***************************************************************************/

#include "Framework/ObjectModel/CommonManagedObjectBase.h"
#include "Framework/ObjectModel/WavePersistableObject.h"
#include "Framework/Utils/TraceUtils.h"

using namespace std;

namespace WaveNs
{

CommonManagedObjectBase::CommonManagedObjectBase (WavePersistableObject *pWavePersistableObject)
    : m_pWavePersistableObject (pWavePersistableObject)
{
    // Do not request for tracking if the Wave Managed Object is being instantiated because of query
#if 0
    if ((WaveThread::getSelf ()) != (WaveThread::getWaveThreadForServiceId (DatabaseObjectManager::getWaveServiceId ()))->getId ())
    {
        pWaveObjectManager->trackObjectCreatedDuringCurrentTransaction (this);

        ObjectTracker::addToObjectTracker (this);
    }

    m_lastModifiedTimeStamp = m_createdTimeStamp;
#endif
}

CommonManagedObjectBase::~CommonManagedObjectBase ()
{
    // Request Object Manager to track this object if necessary.
    // Do not request for tracking if the Wave Managed Object is being instantiated because of query
#if 0
    if ((WaveThread::getSelf ()) != (WaveThread::getWaveThreadForServiceId (DatabaseObjectManager::getWaveServiceId ()))->getId ())
    {
        m_pCurrentOwnerWaveObjectManager->trackObjectDeletedDuringCurrentTransaction (this);
    }

    ObjectTracker::deleteFromObjectTracker (this);
#endif
}

void CommonManagedObjectBase::setupAttributesForPersistence ()
{
}

//#if 0
void CommonManagedObjectBase::addPersistableAttributeForCommonBase(Attribute *pAttribute)
{
    m_pWavePersistableObject->addPersistableAttribute(pAttribute);
}

void CommonManagedObjectBase::addPersistableAttributeForCommonBaseCreate(Attribute *pAttribute)
{
    m_pWavePersistableObject->addPersistableAttributeForCreate(pAttribute);
}
//#endif

void CommonManagedObjectBase::setupAttributesForCreate ()
{
}


}
