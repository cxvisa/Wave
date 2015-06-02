/******************************************************************************************
 *  @file : DatabaseObjectManagerCalculateDbCksumMessage.cpp                              *
 *   Copyright (C) 2010 Vidyasagara Guntaka                                               *
 *   All rights reserved.                                                                 *
 *   Description : Implements a message DatabaseObjectManagerCalculateDbCksumMessage.     *
                   The handler calculates the checksum for the local database.            *
 *   Author : Pritee Ghosh                                                                *
 *   Date   : 02/22/2011                                                                  *
 ******************************************************************************************/
#include "Framework/Database/DatabaseObjectManagerCalculateDbCksumMessage.h"
#include "Framework/Database/DatabaseObjectManager.h"
#include "Framework/Database/DatabaseObjectManagerTypes.h"

namespace WaveNs
{

DatabaseObjectManagerCalculateDbCksumMessage::DatabaseObjectManagerCalculateDbCksumMessage ()
    : PrismMessage (DatabaseObjectManager::getPrismServiceId (), DATABASE_OBJECT_MANAGER_CALCULATE_DB_CKSUM),
      m_pauseTheService (false)  
{
}

DatabaseObjectManagerCalculateDbCksumMessage::~DatabaseObjectManagerCalculateDbCksumMessage ()
{
}

void DatabaseObjectManagerCalculateDbCksumMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

     addSerializableAttribute (new AttributeString   (&m_checksum,          "checksum"));
     addSerializableAttribute (new AttributeBool     (&m_pauseTheService,   "pauseTheService"));
}

string DatabaseObjectManagerCalculateDbCksumMessage::getDbCksumForNode () const
{
    return (m_checksum);
}

void DatabaseObjectManagerCalculateDbCksumMessage::setDbCksumForNode (const string &cksum)
{
    m_checksum = cksum;
}

bool DatabaseObjectManagerCalculateDbCksumMessage::getPauseTheService () const
{
    return (m_pauseTheService);
}

void DatabaseObjectManagerCalculateDbCksumMessage::setPauseTheService (bool pauseTheService) 
{
    m_pauseTheService = pauseTheService;
}
}
