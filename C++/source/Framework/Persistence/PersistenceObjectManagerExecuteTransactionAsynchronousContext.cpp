/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceObjectManagerExecuteTransactionAsynchronousContext.h"

namespace WaveNs
{
    
PersistenceObjectManagerExecuteTransactionAsynchronousContext::PersistenceObjectManagerExecuteTransactionAsynchronousContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_sql                         (""),
      m_isConfigurationChange       (false),
      m_isConfigurationTimeChange   (false),
      m_senderServiceCode           (0),
      m_senderLocationId            (0)
{   
}   

PersistenceObjectManagerExecuteTransactionAsynchronousContext::~PersistenceObjectManagerExecuteTransactionAsynchronousContext ()
{
}
    
string PersistenceObjectManagerExecuteTransactionAsynchronousContext::getSql () const
{
    return (m_sql);
}

void PersistenceObjectManagerExecuteTransactionAsynchronousContext::setSql (const string &sql)
{
    m_sql = sql;
}

bool PersistenceObjectManagerExecuteTransactionAsynchronousContext::getIsConfigurationChange () const
{
    return (m_isConfigurationChange);
}

void PersistenceObjectManagerExecuteTransactionAsynchronousContext::setIsConfigurationChange (const bool &isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

bool PersistenceObjectManagerExecuteTransactionAsynchronousContext::getIsConfigurationTimeChange () const
{
    return (m_isConfigurationTimeChange);
}

void PersistenceObjectManagerExecuteTransactionAsynchronousContext::setIsConfigurationTimeChange (const bool &isConfigurationTimeChange)
{
    m_isConfigurationTimeChange = isConfigurationTimeChange;
}

WaveServiceId PersistenceObjectManagerExecuteTransactionAsynchronousContext::getSenderServiceCode () const
{
    return (m_senderServiceCode);
}

void PersistenceObjectManagerExecuteTransactionAsynchronousContext::setSenderServiceCode (const WaveServiceId &senderServiceCode)
{
    m_senderServiceCode = senderServiceCode;
}

LocationId PersistenceObjectManagerExecuteTransactionAsynchronousContext::getSenderLocationId () const
{
    return (m_senderLocationId);
}

void PersistenceObjectManagerExecuteTransactionAsynchronousContext::setSenderLocationId (const LocationId &senderLocationId)
{
    m_senderLocationId = senderLocationId;
}

}
