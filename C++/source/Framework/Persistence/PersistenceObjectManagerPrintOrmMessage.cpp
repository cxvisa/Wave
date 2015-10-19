/**************************************************************************************
 *  @file : PersistenceObjectManagerPrintOrmMessage.cpp                               *
 *   Copyright (C) 2011 Vidyasagara Guntaka                                           *
 *   All rights reserved.                                                             *
 *   Description : Implements a Persistence OM handled message                        * 
 *   Author : Brian Adaniya                                                           *
 *   Date   : 11/07/2011                                                              *
 **************************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerPrintOrmMessage.h"
#include "Framework/Persistence/PersistenceObjectManager.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"

namespace WaveNs
{

PersistenceObjectManagerPrintOrmMessage::PersistenceObjectManagerPrintOrmMessage ()
    : ManagementInterfaceMessage (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_PRINT_ORM),
    m_ormInfo   ("")
{
}

PersistenceObjectManagerPrintOrmMessage::PersistenceObjectManagerPrintOrmMessage (const vector<string> &arguments)
    : ManagementInterfaceMessage (PersistenceObjectManager::getWaveServiceName (), PERSISTENCE_OBJECT_MANAGER_PRINT_ORM),
    m_ormArgs   (arguments),
    m_ormInfo   ("")
{
}

PersistenceObjectManagerPrintOrmMessage::~PersistenceObjectManagerPrintOrmMessage ()
{
}

void PersistenceObjectManagerPrintOrmMessage::setupAttributesForSerialization ()
{
    ManagementInterfaceMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeStringVector (&m_ormArgs, "ormArgs"));
     addSerializableAttribute (new AttributeString       (&m_ormInfo, "ormInfo"));
}

const vector<string> & PersistenceObjectManagerPrintOrmMessage::getOrmArgs () const
{
    return (m_ormArgs);
}

string PersistenceObjectManagerPrintOrmMessage::getOrmInfo () const
{
    return (m_ormInfo);
}

void PersistenceObjectManagerPrintOrmMessage::setOrmInfo (const string &ormInfo)
{
    m_ormInfo = ormInfo;
}

}
