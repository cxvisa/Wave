/***************************************************************************
*   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Chaitanya Gangwar                                            *
***************************************************************************/

#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"
#include "Framework/Database/DatabaseObjectManagerCreateInMemoryManagedObjectMessage.h"


namespace WaveNs
{

DatabaseObjectManagerCreateInMemoryManagedObjectMessage::DatabaseObjectManagerCreateInMemoryManagedObjectMessage (const  string &className, WaveObjectManager *pWaveObjectManager)
    : PrismMessage          (DatabaseObjectManager::getPrismServiceId (), DATABASE_OBJECT_MANAGER_CREATE_INMEMORY_MO),
    m_className             (className),
    m_pInMemoryManagedObject (NULL),
    m_pWaveObjectManager    (pWaveObjectManager)
{
}


DatabaseObjectManagerCreateInMemoryManagedObjectMessage::~DatabaseObjectManagerCreateInMemoryManagedObjectMessage ()
{
}


string DatabaseObjectManagerCreateInMemoryManagedObjectMessage::getClassName () const
{
    return (m_className);
}


WaveManagedObject *DatabaseObjectManagerCreateInMemoryManagedObjectMessage::getInMemoryMO () const
{
    return (m_pInMemoryManagedObject);
}

void DatabaseObjectManagerCreateInMemoryManagedObjectMessage::setInMemoryMO (WaveManagedObject *inMemoryManagedObject)
{
    m_pInMemoryManagedObject = inMemoryManagedObject;
}

WaveObjectManager *DatabaseObjectManagerCreateInMemoryManagedObjectMessage::getPWaveObjectManager () const
{
    return (m_pWaveObjectManager);
}

}
