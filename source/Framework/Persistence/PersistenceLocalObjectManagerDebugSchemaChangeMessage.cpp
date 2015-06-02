/**************************************************************************************
 *  @file : PersistenceLocalObjectManagerDebugSchemaChangeMessage.cpp                               *
 *   Copyright (C) 2011 Vidyasagara Guntaka                                           *
 *   All rights reserved.                                                             *
 *   Description : Implements a Persistence OM handled message                        * 
 *   Author : Pritee Ghosh                                                            *
 *   Date   : 12/03/2011                                                              *
 **************************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerDebugSchemaChangeMessage.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"

namespace WaveNs
{

PersistenceLocalObjectManagerDebugSchemaChangeMessage::PersistenceLocalObjectManagerDebugSchemaChangeMessage ()
    : ManagementInterfaceMessage (PersistenceLocalObjectManager::getServiceName (), PERSISTENCE_DEBUG_SCHEMA_CHANGE)
{
}

PersistenceLocalObjectManagerDebugSchemaChangeMessage::PersistenceLocalObjectManagerDebugSchemaChangeMessage (const vector<string> &arguments)
    : ManagementInterfaceMessage (PersistenceLocalObjectManager::getServiceName (), PERSISTENCE_DEBUG_SCHEMA_CHANGE),
    m_cmdArgs     (arguments),
    m_resultPrint ("")
{
}   

PersistenceLocalObjectManagerDebugSchemaChangeMessage::~PersistenceLocalObjectManagerDebugSchemaChangeMessage ()
{
}

void PersistenceLocalObjectManagerDebugSchemaChangeMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_cmdArgs,       "cmdArgs"));
     addSerializableAttribute (new AttributeString       (&m_resultPrint,   "resultPrint"));
}

const vector<string> & PersistenceLocalObjectManagerDebugSchemaChangeMessage::getCmdArgs () const
{
    return (m_cmdArgs);
}

string PersistenceLocalObjectManagerDebugSchemaChangeMessage::getResultPrint () const
{
    return (m_resultPrint);
}

void PersistenceLocalObjectManagerDebugSchemaChangeMessage::setResultPrint (const string &result)
{
    m_resultPrint = result;
}

}
