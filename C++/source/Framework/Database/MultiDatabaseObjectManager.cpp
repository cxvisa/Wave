/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Database/MultiDatabaseObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryWorker.h"
#include "Framework/Database/MultiDatabaseObjectManagerSetupServersWorker.h"
#include "Framework/Database/DatabaseObjectManagerExecuteQueryMessage.h"
#include "Framework/Database/DatabaseObjectManagerExecuteCursorCommandWorker.h"
#include "Framework/Database/MultiDatabaseToolKit.h"

namespace WaveNs
{

MultiDatabaseObjectManager::MultiDatabaseObjectManager ()
    : WaveLocalObjectManager (getClassName ())
{
    MultiDatabaseToolKit::setIsMultiModeEnabled (true);

    DatabaseObjectManagerExecuteQueryMessage::setDatabaseObjectManagerServiceId (getServiceId ());

    m_pDatabaseObjectManagerExecuteQueryWorker = new DatabaseObjectManagerExecuteQueryWorker (this, true);

    waveAssert (NULL != m_pDatabaseObjectManagerExecuteQueryWorker, __FILE__, __LINE__);

    m_pMultiDatabaseObjectManagerSetupServersWorker = new MultiDatabaseObjectManagerSetupServersWorker (this);

    waveAssert (NULL != m_pMultiDatabaseObjectManagerSetupServersWorker, __FILE__, __LINE__);

    m_pDatabaseObjectManagerExecuteCursorCommandWorker = new DatabaseObjectManagerExecuteCursorCommandWorker (this, true);

    waveAssert (NULL != m_pDatabaseObjectManagerExecuteCursorCommandWorker, __FILE__, __LINE__);
}

MultiDatabaseObjectManager::~MultiDatabaseObjectManager ()
{
    if (NULL != m_pDatabaseObjectManagerExecuteQueryWorker)
    {
        delete m_pDatabaseObjectManagerExecuteQueryWorker;

        m_pDatabaseObjectManagerExecuteQueryWorker = NULL;
    }

    if (NULL != m_pMultiDatabaseObjectManagerSetupServersWorker)
    {
        delete m_pMultiDatabaseObjectManagerSetupServersWorker;

        m_pMultiDatabaseObjectManagerSetupServersWorker = NULL;
    }

    if (NULL != m_pDatabaseObjectManagerExecuteCursorCommandWorker)
    {
        delete m_pDatabaseObjectManagerExecuteCursorCommandWorker;

        m_pDatabaseObjectManagerExecuteCursorCommandWorker = NULL;
    }
}

MultiDatabaseObjectManager *MultiDatabaseObjectManager::getInstance ()
{
    static MultiDatabaseObjectManager *pMultiDatacaseObjectManager = NULL;

    if (NULL == pMultiDatacaseObjectManager)
    {
        pMultiDatacaseObjectManager = new MultiDatabaseObjectManager ();

        WaveNs::waveAssert (NULL != pMultiDatacaseObjectManager, __FILE__, __LINE__);
    }

    return (pMultiDatacaseObjectManager);
}

WaveServiceId MultiDatabaseObjectManager::getWaveServiceId ()
{
    return ((getInstance ())->getServiceId ());
}

string MultiDatabaseObjectManager::getClassName ()
{
    return ("Multi Wave Database");
}

void MultiDatabaseObjectManager::boot (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases)
{
    pWaveAsynchronousContextForBootPhases->setCompletionStatus (WAVE_MESSAGE_SUCCESS);
    pWaveAsynchronousContextForBootPhases->callback ();
}

WaveManagedObject *MultiDatabaseObjectManager::loadWaveManagedObjectFromDatabase (const ObjectId &waveManagedObjectObjectId, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return (m_pDatabaseObjectManagerExecuteQueryWorker->loadWaveManagedObjectFromDatabase (waveManagedObjectObjectId, schema, pWaveObjectManager));
}

WaveManagedObject *MultiDatabaseObjectManager::loadWaveManagedObjectFromDatabaseWrapper (const ObjectId &waveManagedObjectObjectId, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return ((getInstance ())->loadWaveManagedObjectFromDatabase (waveManagedObjectObjectId, schema, pWaveObjectManager));
}

vector<WaveManagedObject *> MultiDatabaseObjectManager::loadWaveManagedObjectsFromDatabase (const vector<ObjectId> &waveManagedObjectObjectIds, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return (m_pDatabaseObjectManagerExecuteQueryWorker->loadWaveManagedObjectsFromDatabase (waveManagedObjectObjectIds, schema, pWaveObjectManager));
}

vector<WaveManagedObject *> MultiDatabaseObjectManager::loadWaveManagedObjectsFromDatabaseWrapper (const vector<ObjectId> &waveManagedObjectObjectIds, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return ((getInstance ())->loadWaveManagedObjectsFromDatabase (waveManagedObjectObjectIds, schema, pWaveObjectManager));
}

vector<WaveManagedObject *> MultiDatabaseObjectManager::loadWaveManagedObjectsFromDatabase (const string &childClassName, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return (m_pDatabaseObjectManagerExecuteQueryWorker->loadWaveManagedObjectsFromDatabase (childClassName, parentObjectId, schema, pWaveObjectManager));
}

vector<WaveManagedObject *> MultiDatabaseObjectManager::loadWaveManagedObjectsFromDatabaseWrapper (const string &childClassName, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager)
{
    return ((getInstance ())->loadWaveManagedObjectsFromDatabase (childClassName, parentObjectId, schema, pWaveObjectManager));
}


}
