/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerSetStartupFileMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"
#include "Framework/Attributes/AttributeEnum.h"

namespace WaveNs
{

PersistenceLocalObjectManagerSetStartupFileMessage::PersistenceLocalObjectManagerSetStartupFileMessage (const ResourceId &startupFileType, const string &fileName)
    : WaveMessage      (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SET_STARTUP_FILE),
      m_startupFileType (startupFileType),
      m_fileName        (fileName)
{
}

PersistenceLocalObjectManagerSetStartupFileMessage::PersistenceLocalObjectManagerSetStartupFileMessage ()
    : WaveMessage (PersistenceLocalObjectManager::getWaveServiceId (), PERSISTENCE_SET_STARTUP_FILE),
      m_startupFileType(0)
{
}

PersistenceLocalObjectManagerSetStartupFileMessage::~PersistenceLocalObjectManagerSetStartupFileMessage ()
{
}

void PersistenceLocalObjectManagerSetStartupFileMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString  (&m_fileName,        "fileName"));
     addSerializableAttribute (new AttributeEnum    (&m_startupFileType, "startupFileType"));
}

string PersistenceLocalObjectManagerSetStartupFileMessage::getStartupFileName () const
{
    return (m_fileName);
}

void PersistenceLocalObjectManagerSetStartupFileMessage::setStartupFileName (const string &fileName)
{
    m_fileName = fileName;
}

ResourceId PersistenceLocalObjectManagerSetStartupFileMessage::getStartupFileType () const
{
    return (m_startupFileType);
}

void PersistenceLocalObjectManagerSetStartupFileMessage::setStartupFileType (const ResourceId &startupFileType)
{
    m_startupFileType = startupFileType;
}

}
