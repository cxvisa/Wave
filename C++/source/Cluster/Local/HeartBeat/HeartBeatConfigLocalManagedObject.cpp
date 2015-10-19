/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jvenkata                                                     *
 **************************************************************************/

#include "Cluster/Local/HeartBeat/HeartBeatConfigLocalManagedObject.h"
#include "Cluster/Local/HeartBeat/HeartBeatObjectManager.h"

namespace WaveNs
{

    HeartBeatConfigLocalManagedObject::HeartBeatConfigLocalManagedObject (HeartBeatObjectManager *pHeartBeatObjectManager)
        : WaveElement  (pHeartBeatObjectManager),
        WavePersistableObject (HeartBeatConfigLocalManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
        WaveManagedObject (pHeartBeatObjectManager),
        WaveLocalManagedObjectBase (this),
        WaveLocalManagedObject (pHeartBeatObjectManager),
        m_defaultHeartBeatInterval (0),
        m_defaultHeartBeatFailureThreshold (0)
    {
    }

    HeartBeatConfigLocalManagedObject::HeartBeatConfigLocalManagedObject (HeartBeatObjectManager *pHeartBeatObjectManager,const UI32 &defaultHeartBeatInterval,const UI32 &defaultHeartBeatFailureThreshold)
        : WaveElement  (pHeartBeatObjectManager),
        WavePersistableObject (HeartBeatConfigLocalManagedObject::getClassName (), WaveLocalManagedObject::getClassName ()),
        WaveManagedObject (pHeartBeatObjectManager),
        WaveLocalManagedObjectBase (this),
        WaveLocalManagedObject (pHeartBeatObjectManager),
        m_defaultHeartBeatInterval    (defaultHeartBeatInterval),
        m_defaultHeartBeatFailureThreshold    (defaultHeartBeatFailureThreshold)
    {
    }

    HeartBeatConfigLocalManagedObject::~HeartBeatConfigLocalManagedObject ()
    {
    }

    string  HeartBeatConfigLocalManagedObject::getClassName() 
    {
        return ("HeartBeatConfigLocalManagedObject");
    }

    void  HeartBeatConfigLocalManagedObject::setupAttributesForPersistence()
    {
        WaveLocalManagedObject::setupAttributesForPersistence ();
        addPersistableAttribute (new AttributeUI32(&m_defaultHeartBeatInterval,"defaultHeartBeatInterval"));
        addPersistableAttribute (new AttributeUI32(&m_defaultHeartBeatFailureThreshold,"defaultHeartBeatFailureThreshold"));
    }

    void  HeartBeatConfigLocalManagedObject::setupAttributesForCreate()
    {
        WaveLocalManagedObject::setupAttributesForCreate ();
        addPersistableAttributeForCreate  (new AttributeUI32(&m_defaultHeartBeatInterval,"defaultHeartBeatInterval"));
        addPersistableAttributeForCreate  (new AttributeUI32(&m_defaultHeartBeatFailureThreshold,"defaultHeartBeatFailureThreshold"));
    }

    void  HeartBeatConfigLocalManagedObject::setDefaultHeartBeatInterval(const UI32 &defaultHeartBeatInterval)
    {
        m_defaultHeartBeatInterval  =  defaultHeartBeatInterval;
    }

    UI32  HeartBeatConfigLocalManagedObject::getDefaultHeartBeatInterval() const
    {
        return (m_defaultHeartBeatInterval);
    }

    void  HeartBeatConfigLocalManagedObject::setDefaultHeartBeatFailureThreshold(const UI32 &defaultHeartBeatFailureThreshold)
    {
        m_defaultHeartBeatFailureThreshold  =  defaultHeartBeatFailureThreshold;
    }

    UI32  HeartBeatConfigLocalManagedObject::getDefaultHeartBeatFailureThreshold() const
    {
        return (m_defaultHeartBeatFailureThreshold);
    }

}
