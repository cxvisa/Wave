/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerCopySchemaMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerCopySchemaMessage::PersistenceLocalObjectManagerCopySchemaMessage (const string &sourceSchema, const string &destSchema)
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_COPY_SCHEMA),
      m_sourceSchema (sourceSchema),
      m_destSchema (destSchema)
{
}

PersistenceLocalObjectManagerCopySchemaMessage::PersistenceLocalObjectManagerCopySchemaMessage ()
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_COPY_SCHEMA)
{
}

PersistenceLocalObjectManagerCopySchemaMessage::~PersistenceLocalObjectManagerCopySchemaMessage ()
{
}

void PersistenceLocalObjectManagerCopySchemaMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_sourceSchema,    "sourceSchema"));
     addSerializableAttribute (new AttributeString (&m_destSchema,      "destSchema"));
}

string PersistenceLocalObjectManagerCopySchemaMessage::getSourceSchema () const
{
    return (m_sourceSchema);
}

void PersistenceLocalObjectManagerCopySchemaMessage::setSourceSchema (const string &sourceSchema)
{
    m_sourceSchema = sourceSchema;
}

string PersistenceLocalObjectManagerCopySchemaMessage::getDestSchema () const
{
    return (m_destSchema);
}

void PersistenceLocalObjectManagerCopySchemaMessage::setDestSchema (const string &destSchema)
{
    m_destSchema = destSchema;
}

}
