/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerCopyFileMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Attributes/AttributeEnum.h"

namespace WaveNs
{

PersistenceObjectManagerCopyFileMessage::PersistenceObjectManagerCopyFileMessage (const ResourceId &startupFileType, const string &startupFileName, const bool &isLocalFileCopy)
    : WaveMessage (PersistenceObjectManager::getWaveServiceId (), PERSISTENCE_OBNJECT_MANAGER_COPY_FILE),
      m_startupFileType (startupFileType),
      m_startupFileName (startupFileName),
      m_isLocalFileCopy (isLocalFileCopy)
{
}

PersistenceObjectManagerCopyFileMessage::PersistenceObjectManagerCopyFileMessage ()
    : WaveMessage (PersistenceObjectManager::getWaveServiceId (), PERSISTENCE_OBNJECT_MANAGER_COPY_FILE),
      m_startupFileType (0),
      m_isLocalFileCopy(false)
{
}

PersistenceObjectManagerCopyFileMessage::~PersistenceObjectManagerCopyFileMessage ()
{
}

void PersistenceObjectManagerCopyFileMessage::setupAttributesForSerialization ()
{
    WaveMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_startupFileName, "startupFileName"));
     addSerializableAttribute (new AttributeEnum (&m_startupFileType,   "startupFileType"));
     addSerializableAttribute (new AttributeBool (&m_isLocalFileCopy,   "isLocalFileCopy"));
}

string PersistenceObjectManagerCopyFileMessage::getStartupFileName () const
{
    return (m_startupFileName);
}

void PersistenceObjectManagerCopyFileMessage::setStartupFileName (const string &startupFileName)
{
    m_startupFileName = startupFileName;
}

ResourceId PersistenceObjectManagerCopyFileMessage::getStartupFileType () const
{
    return (m_startupFileType);
}

void PersistenceObjectManagerCopyFileMessage::setStartupFileType (const ResourceId &startupFileType)
{
    m_startupFileType = startupFileType;
}

bool PersistenceObjectManagerCopyFileMessage::getIsLocalFileCopy () const
{
    return (m_isLocalFileCopy);
}

void PersistenceObjectManagerCopyFileMessage::setIsLocalFileCopy (const bool &isLocalFileCopy)
{
    m_isLocalFileCopy =isLocalFileCopy;
}
}
