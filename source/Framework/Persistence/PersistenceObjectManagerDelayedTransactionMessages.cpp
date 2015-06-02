/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerDelayedTransactionMessages.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceObjectManager.h"

namespace WaveNs
{

PersistenceObjectManagerAddDelayedTransactionMessage::PersistenceObjectManagerAddDelayedTransactionMessage (const string &sql)
    : PrismMessage (PersistenceObjectManager::getPrismServiceId (), PERSISTENCE_OBJECT_MANAGER_ADD_DELAYED_TRANSACTION),
    m_sql (sql)
{
}

PersistenceObjectManagerAddDelayedTransactionMessage::PersistenceObjectManagerAddDelayedTransactionMessage ()
    : PrismMessage (PersistenceObjectManager::getPrismServiceId (), PERSISTENCE_OBJECT_MANAGER_ADD_DELAYED_TRANSACTION),
    m_sql ("")
{
}

PersistenceObjectManagerAddDelayedTransactionMessage::~PersistenceObjectManagerAddDelayedTransactionMessage ()
{
}

void PersistenceObjectManagerAddDelayedTransactionMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_sql, "sql"));
}

string PersistenceObjectManagerAddDelayedTransactionMessage::getSql () const
{
    return (m_sql);
}

void PersistenceObjectManagerAddDelayedTransactionMessage::setSql (const string &sql)
{
    m_sql = sql;
}

}
