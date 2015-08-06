/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/DatabaseObjectManagerExecuteCopySchemaMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerExecuteCopySchemaMessage::DatabaseObjectManagerExecuteCopySchemaMessage (const string &prepareString, const string &sourceSchema, const string &destSchema)
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_COPY_SCHEMA),
      m_pResults (NULL),
      m_prepareString (prepareString),
      m_sourceSchema (sourceSchema),
      m_destSchema (destSchema)
{
}

DatabaseObjectManagerExecuteCopySchemaMessage::DatabaseObjectManagerExecuteCopySchemaMessage (const string &sourceSchema, const string &destSchema)
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_COPY_SCHEMA),
      m_pResults (NULL),
      m_prepareString (""),
      m_sourceSchema (sourceSchema),
      m_destSchema (destSchema)
{
}

DatabaseObjectManagerExecuteCopySchemaMessage::DatabaseObjectManagerExecuteCopySchemaMessage ()
    : PrismMessage (DatabaseObjectManager::getWaveServiceId (), DATABASE_OBJECT_MANAGER_EXECUTE_COPY_SCHEMA),
      m_pResults (NULL),
      m_prepareString (""),
      m_sourceSchema (""),
      m_destSchema ("")
{
}

DatabaseObjectManagerExecuteCopySchemaMessage::~DatabaseObjectManagerExecuteCopySchemaMessage ()
{
}

void DatabaseObjectManagerExecuteCopySchemaMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString (&m_prepareString,   "prepareString"));
     addSerializableAttribute (new AttributeString (&m_sourceSchema,    "sourceSchema"));
     addSerializableAttribute (new AttributeString (&m_destSchema,      "destSchema"));
}

void DatabaseObjectManagerExecuteCopySchemaMessage::setPResults (vector<WaveManagedObject *> *pResults)
{
    m_pResults = pResults;
}

vector<WaveManagedObject *> *DatabaseObjectManagerExecuteCopySchemaMessage::getPResults () const
{
    return (m_pResults);
}

string DatabaseObjectManagerExecuteCopySchemaMessage::getPrepareString () const
{
    return (m_prepareString);
}

void DatabaseObjectManagerExecuteCopySchemaMessage::setPrepareString (const string &prepareString)
{
    m_prepareString = prepareString;
}

string DatabaseObjectManagerExecuteCopySchemaMessage::getSourceSchema () const
{
    return (m_sourceSchema);
}

void DatabaseObjectManagerExecuteCopySchemaMessage::setSourceSchema (const string &sourceSchema)
{
    m_sourceSchema = sourceSchema;
}

string DatabaseObjectManagerExecuteCopySchemaMessage::getDestSchema () const
{
    return (m_destSchema);
}

void DatabaseObjectManagerExecuteCopySchemaMessage::setDestSchema (const string &destSchema)
{
    m_destSchema = destSchema;
}

}
