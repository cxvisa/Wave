/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Persistence/PersistenceExecuteTransactionContext.h"

namespace WaveNs
{

PersistenceExecuteTransactionContext::PersistenceExecuteTransactionContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps, const string &sql)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_currentTransactionId        (0),
      m_startupFileType             (0),
      m_isStartupValid              (false),
      m_isLocalFileCopy             (false),
      m_pConfigurationManagedObject (NULL),
      m_sql                         (sql),
      m_isConfigurationChange       (false),
      m_isConfigurationTimeChange   (false),
      m_senderServiceCode           (0),
      m_senderLocationId            (0)
{
}

#if 0
PersistenceExecuteTransactionContext::PersistenceExecuteTransactionContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveAsynchronousContext, pWaveElement, pSteps, numberOfSteps),
      m_currentTransactionId        (0),
      m_startupFileType             (0),
      m_isStartupValid              (false),
      m_isLocalFileCopy             (false),
      m_pConfigurationManagedObject (NULL),
      m_sql                         (""),
      m_isConfigurationChange       (false),
      m_isConfigurationTimeChange   (false),
      m_senderServiceCode           (0),
      m_senderLocationId            (0)
{
}
#endif

PersistenceExecuteTransactionContext::~PersistenceExecuteTransactionContext ()
{
    if (NULL != m_pConfigurationManagedObject)
    {
        delete m_pConfigurationManagedObject;
    }
}

vector<LocationId> &PersistenceExecuteTransactionContext::getCurrentLocationIds ()
{
    return (m_currentLocationIds);
}

map<LocationId, ResourceId> &PersistenceExecuteTransactionContext::getTransactionStatusForCurrentLocations ()
{
    return (m_transactionStatusForCurrentLocations);
}

UI32 PersistenceExecuteTransactionContext::getCurrentTransactionId () const
{
    return (m_currentTransactionId);
}

void PersistenceExecuteTransactionContext::setCurrentTransactionId (const UI32 &currentTransactionId)
{
    m_currentTransactionId = currentTransactionId;
}

string PersistenceExecuteTransactionContext::getSourceSchema () const
{
    return (m_sourceSchema);
}

void PersistenceExecuteTransactionContext::setSourceSchema (const string &sourceSchema)
{
    m_sourceSchema = sourceSchema;
}

string PersistenceExecuteTransactionContext::getDestSchema () const
{
    return (m_destSchema);
}

void PersistenceExecuteTransactionContext::setDestSchema (const string &destSchema)
{
    m_destSchema = destSchema;
}

string PersistenceExecuteTransactionContext::getStartupFileName () const
{
    return (m_startupFileName);
}

void PersistenceExecuteTransactionContext::setStartupFileName (const string &startupFileName)
{
    m_startupFileName = startupFileName;
}

ResourceId PersistenceExecuteTransactionContext::getStartupFileType () const
{
    return (m_startupFileType);
}

void PersistenceExecuteTransactionContext::setStartupFileType (const ResourceId &startupFileType)
{
    m_startupFileType = startupFileType;
}

bool PersistenceExecuteTransactionContext::getIsStartupValid () const
{
    return (m_isStartupValid);
}

void PersistenceExecuteTransactionContext::setIsStartupValid (const bool &isStartupValid)
{
    m_isStartupValid =isStartupValid;
}

bool PersistenceExecuteTransactionContext::getIsLocalFileCopy () const
{
    return (m_isLocalFileCopy);
}

void PersistenceExecuteTransactionContext::setIsLocalFileCopy (const bool &isLocalFileCopy)
{
    m_isLocalFileCopy =isLocalFileCopy;
}

void PersistenceExecuteTransactionContext::setConfigurationManagedObject (ConfigurationManagedObject *pConfigurationManagedObject)
{
    m_pConfigurationManagedObject = pConfigurationManagedObject;
}

ConfigurationManagedObject* PersistenceExecuteTransactionContext::getConfigurationManagedObject ()
{
    return (m_pConfigurationManagedObject);
}

vector<string>& PersistenceExecuteTransactionContext::getxPathStringsVectorForTimestampUpdate ()
{
    return m_xPathStringsVectorForTimestampUpdate;
}

map<string, DateTime>& PersistenceExecuteTransactionContext::getxPathStringToOriginalDatetimestampMap ()
{
    return m_xPathStringToOriginalDatetimestampMap;
}

const string &PersistenceExecuteTransactionContext::getSql () const
{
    return (m_sql);
}

#if 0
void PersistenceExecuteTransactionContext::setSql (const string &sql)
{
    m_sql = sql;
}
#endif

bool PersistenceExecuteTransactionContext::getIsConfigurationChange () const
{
    return (m_isConfigurationChange);
}

void PersistenceExecuteTransactionContext::setIsConfigurationChange (const bool &isConfigurationChange)
{
    m_isConfigurationChange = isConfigurationChange;
}

bool PersistenceExecuteTransactionContext::getIsConfigurationTimeChange () const
{
    return (m_isConfigurationTimeChange);
}

void PersistenceExecuteTransactionContext::setIsConfigurationTimeChange (const bool &isConfigurationTimeChange)
{
    m_isConfigurationTimeChange = isConfigurationTimeChange;
}

WaveServiceId PersistenceExecuteTransactionContext::getSenderServiceCode () const
{
    return (m_senderServiceCode);
}

void PersistenceExecuteTransactionContext::setSenderServiceCode (const WaveServiceId &senderServiceCode)
{
    m_senderServiceCode = senderServiceCode;
}

LocationId PersistenceExecuteTransactionContext::getSenderLocationId () const
{
    return (m_senderLocationId);
}

void PersistenceExecuteTransactionContext::setSenderLocationId (const LocationId &senderLocationId)
{
    m_senderLocationId = senderLocationId;
}

void PersistenceExecuteTransactionContext::setConfigNamesForInsert (const vector<string> &configNamesForInsert)
{
    m_configNamesForInsert = configNamesForInsert;
}   

vector<string> PersistenceExecuteTransactionContext::getConfigNamesForInsert () const
{
    return (m_configNamesForInsert);
}   

void PersistenceExecuteTransactionContext::setConfigValuesForInsert (const vector<string> &configValuesForInsert)
{
    m_configValuesForInsert = configValuesForInsert;
}   

vector<string> PersistenceExecuteTransactionContext::getConfigValuesForInsert () const
{
    return (m_configValuesForInsert);
}   

void PersistenceExecuteTransactionContext::setConfigTypesForInsert (const vector<ResourceId> &configTypesForInsert)
{
    m_configTypesForInsert = configTypesForInsert;
}

vector<ResourceId> PersistenceExecuteTransactionContext::getConfigTypesForInsert () const
{               
    return (m_configTypesForInsert);
}               
                
void PersistenceExecuteTransactionContext::setConfigNamesForUpdate (const vector<string> &configNamesForUpdate)
{
    m_configNamesForUpdate = configNamesForUpdate;
}               
                
vector<string> PersistenceExecuteTransactionContext::getConfigNamesForUpdate () const
{               
    return (m_configNamesForUpdate);
}   

void PersistenceExecuteTransactionContext::setConfigValuesForUpdate (const vector<string> &configValuesForUpdate)
{       
    m_configValuesForUpdate = configValuesForUpdate;
}       
        
vector<string> PersistenceExecuteTransactionContext::getConfigValuesForUpdate () const
{
    return (m_configValuesForUpdate);
}

void PersistenceExecuteTransactionContext::setConfigTypesForUpdate (const vector<ResourceId> &configTypesForUpdate)
{
    m_configTypesForUpdate = configTypesForUpdate;
}

vector<ResourceId> PersistenceExecuteTransactionContext::getConfigTypesForUpdate () const
{
    return (m_configTypesForUpdate);
}

}
