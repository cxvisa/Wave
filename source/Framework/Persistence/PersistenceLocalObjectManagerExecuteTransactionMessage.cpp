/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceLocalObjectManagerExecuteTransactionMessage.h"
#include "Framework/Persistence/PersistenceObjectManagerTypes.h"
#include "Framework/Persistence/PersistenceLocalObjectManager.h"

namespace WaveNs
{

PersistenceLocalObjectManagerExecuteTransactionMessage::PersistenceLocalObjectManagerExecuteTransactionMessage (const string &sql, const UI32 &transactionId)
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_LOCAL_OBJECT_MANAGER_EXECUTE_TRANSACTION),
      m_sql (sql),
      m_isCommit (false),
      m_isRollback (false),
      m_transactionId (transactionId),
      m_isPrepare (false),
      m_isConfigurationChange (false),
      m_isConfigurationTimeChange (false),
      m_anyConfigurationChangeTrackingNumber (0)
{
}

PersistenceLocalObjectManagerExecuteTransactionMessage::PersistenceLocalObjectManagerExecuteTransactionMessage ()
    : PrismMessage (PersistenceLocalObjectManager::getPrismServiceId (), PERSISTENCE_LOCAL_OBJECT_MANAGER_EXECUTE_TRANSACTION),
      m_sql (""),
      m_isCommit (false),
      m_isRollback (false),
      m_transactionId (0),
      m_isPrepare (false),
      m_isConfigurationChange (false),
      m_isConfigurationTimeChange (false),
      m_anyConfigurationChangeTrackingNumber (0)
{
}

PersistenceLocalObjectManagerExecuteTransactionMessage::~PersistenceLocalObjectManagerExecuteTransactionMessage ()
{
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setupAttributesForSerialization ()
{
    PrismMessage::setupAttributesForSerialization ();

    addSerializableAttribute (new AttributeString (&m_sql,                                  "sql"));
    addSerializableAttribute (new AttributeBool   (&m_isCommit,                             "isCommit"));
    addSerializableAttribute (new AttributeBool   (&m_isRollback,                           "isRollback"));
    addSerializableAttribute (new AttributeUI32   (&m_transactionId,                        "transactionId"));
    addSerializableAttribute (new AttributeBool   (&m_isPrepare,                            "isPrepare"));
    addSerializableAttribute (new AttributeBool   (&m_isConfigurationChange,                "isConfigurationChange"));
    addSerializableAttribute (new AttributeBool   (&m_isConfigurationTimeChange,            "isConfigurationTimeChange"));
    addSerializableAttribute (new AttributeUI64   (&m_anyConfigurationChangeTrackingNumber, "anyConfigurationChangeTrackingNumber"));
}

const string &PersistenceLocalObjectManagerExecuteTransactionMessage::getSql () const
{
    return (m_sql);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setSql (const string &sql)
{
    m_sql = sql;
}

bool PersistenceLocalObjectManagerExecuteTransactionMessage::getIsCommit () const
{
    return (m_isCommit);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setIsCommit (const bool &isCommit)
{
    m_isCommit = isCommit;
}

bool PersistenceLocalObjectManagerExecuteTransactionMessage::getIsRollback () const
{
    return (m_isRollback);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setIsRollback (const bool &isRollback)
{
    m_isRollback = isRollback;
}

UI32 PersistenceLocalObjectManagerExecuteTransactionMessage::getTransactionId () const
{
    return (m_transactionId);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setTransactionId (const UI32 &transactionId)
{
    m_transactionId = transactionId;
}

bool PersistenceLocalObjectManagerExecuteTransactionMessage::getIsPrepare () const
{
    return (m_isPrepare);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setIsPrepare (const bool &isPrepare)
{
    m_isPrepare = isPrepare;
}

bool PersistenceLocalObjectManagerExecuteTransactionMessage::getIsConfigurationChange() const
{
    return (m_isConfigurationChange);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setIsConfigurationChange (const bool &isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

bool PersistenceLocalObjectManagerExecuteTransactionMessage::getIsConfigurationTimeChange () const
{
    return (m_isConfigurationTimeChange);
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setIsConfigurationTimeChange (const bool &isConfigurationTimeChange)
{
    m_isConfigurationTimeChange = isConfigurationTimeChange;
}

void PersistenceLocalObjectManagerExecuteTransactionMessage::setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber)
{
    m_anyConfigurationChangeTrackingNumber = trackingNumber;
}

UI64 PersistenceLocalObjectManagerExecuteTransactionMessage::getAnyConfigurationChangeTrackingNumber () const
{
    return (m_anyConfigurationChangeTrackingNumber);
}

}
