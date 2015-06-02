/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerCopySchemaMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerCopySchemaMessage::PersistenceObjectManagerCopySchemaMessage (const string &sourceSchema, const string &destSchema)
    : PrismMessage (PersistenceObjectManager::getPrismServiceId (), PERSISTENCE_OBNJECT_MANAGER_COPY_SCHEMA),
      m_sourceSchema (sourceSchema),
      m_destSchema (destSchema)
{
}

PersistenceObjectManagerCopySchemaMessage::PersistenceObjectManagerCopySchemaMessage ()
    : PrismMessage (PersistenceObjectManager::getPrismServiceId (), PERSISTENCE_OBNJECT_MANAGER_COPY_SCHEMA)
{
}

PersistenceObjectManagerCopySchemaMessage::~PersistenceObjectManagerCopySchemaMessage ()
{
}

void PersistenceObjectManagerCopySchemaMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_sourceSchema, "sourceSchema"));
     addSerializableAttribute (new AttributeString (&m_destSchema,   "destSchema"));
}

string PersistenceObjectManagerCopySchemaMessage::getSourceSchema () const
{
    return (m_sourceSchema);
}

void PersistenceObjectManagerCopySchemaMessage::setSourceSchema (const string &sourceSchema)
{
    m_sourceSchema = sourceSchema;
}

string PersistenceObjectManagerCopySchemaMessage::getDestSchema () const
{
    return (m_destSchema);
}

void PersistenceObjectManagerCopySchemaMessage::setDestSchema (const string &destSchema)
{
    m_destSchema = destSchema;
}

}
