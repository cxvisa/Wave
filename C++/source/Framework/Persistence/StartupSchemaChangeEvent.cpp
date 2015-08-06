/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Kadu                                                  *
 ***************************************************************************/

#include "Framework/Persistence/StartupSchemaChangeEvent.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"
#include "Framework/Attributes/AttributeEnum.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

StartupSchemaChangeEvent::StartupSchemaChangeEvent ()
    : PrismEvent (PersistenceLocalObjectManager::getWaveServiceId (), STARTUP_SCHEMA_CHANGE_EVENT),
      m_operationStatus(1), 
      m_fromSchema (RUNNING_SCHEMA),
      m_pathForFromSchemaFile (""),
      m_toSchema (STARTUP_SCHEMA),
      m_pathForToSchemaFile ("")
{
}

StartupSchemaChangeEvent::~StartupSchemaChangeEvent ()
{
}

void StartupSchemaChangeEvent::setupAttributesForSerialization ()
{
    PrismEvent::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeBool           (&m_operationStatus,          "operationStatus"));
    addSerializableAttribute (new AttributeEnum ((UI32 *) (&m_fromSchema),              "fromSchema"));
    addSerializableAttribute (new AttributeString         (&m_pathForFromSchemaFile,    "pathForFromSchemaFile"));
    addSerializableAttribute (new AttributeEnum ((UI32 *) (&m_toSchema),                "toSchema"));
    addSerializableAttribute (new AttributeString         (&m_pathForToSchemaFile,      "pathForToSchemaFile"));
}

void StartupSchemaChangeEvent::setOperationStatus (const bool isOpComplete)
{
    m_operationStatus = isOpComplete;
}

bool StartupSchemaChangeEvent::getOperationStatus () const
{
    return (m_operationStatus);
}

void StartupSchemaChangeEvent::setFromSchema (const SchemaType schemaCopiedFrom)
{
   m_fromSchema = schemaCopiedFrom;
}

SchemaType StartupSchemaChangeEvent::getFromSchema () const
{
    return (m_fromSchema);
}

void StartupSchemaChangeEvent::setToSchema (const SchemaType schemaCopiedTo)
{
   m_toSchema = schemaCopiedTo;
}

SchemaType StartupSchemaChangeEvent::getToSchema () const
{
    return (m_toSchema);
}

void StartupSchemaChangeEvent::setFromFileSchemaPath (const string &fileCopiedFromSchema)
{
    m_pathForFromSchemaFile = fileCopiedFromSchema;
}

string StartupSchemaChangeEvent::getFromFileSchemaPath () const
{
    return (m_pathForFromSchemaFile);
}

void StartupSchemaChangeEvent::setToFileSchemaPath (const string &fileCopiedToSchema)
{
    m_pathForToSchemaFile = fileCopiedToSchema;
}

string StartupSchemaChangeEvent::getToFileSchemaPath () const
{
    return (m_pathForToSchemaFile);
}

string StartupSchemaChangeEvent::getSchemaName (const SchemaType schemaEnumValue) const
{
    string schemaName = "";
    switch (schemaEnumValue)
    {
        case RUNNING_SCHEMA :
            schemaName = "RUNNING_SCHEMA";
            break;
        case DEFAULT_SCHEMA :
            schemaName = "DEFAULT_SCHEMA";
            break;
        case STARTUP_SCHEMA :
            schemaName = "STARTUP_SCHEMA";
            break;
        case SCHEMA_FILE :
            schemaName = "CONFIG_FILE";
            break;
        default:
            trace (TRACE_LEVEL_INFO, "StartupSchemaChangeEvent::getSchemaName: unsupported SchemaType");
    }
    
    return (schemaName);
    
}

}
