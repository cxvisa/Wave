/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTEQUERYWORKER_H
#define DATABASEOBJECTMANAGEREXECUTEQUERYWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Database/DatabaseObjectManagerGetDBSchemaInfoMessage.h"
#include "Framework/Database/DatabaseObjectManagerDropAllDBViewsMessage.h"

#include "libpq-fe.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveObjectManager;
class DatabaseObjectManagerExecuteQueryMessage;
class DatabaseObjectManagerExecuteQueryMessageForCount;
class WaveAsynchronousContextForDebugInformation;
class DatabaseObjectManagerDebugChangeQuerySettingsMessage;

class DatabaseObjectManagerExecuteQueryWorker : public WaveWorker
{
    private :

        class RecursiveQueryContext
        {
            public:
                WaveObjectManager      *m_pWaveObjectManager;
                WaveObjectManager      *m_pRequestingWaveObjectManager;
                string                  m_schemaToQuery;
                bool                    m_loadOneToManyRelationShips;
                bool                    m_loadCompositions;
        };

        virtual void    getDebugInformation         (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
        virtual void    resetDebugInformation       (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

                PGconn *getDatabaseServerConnection (const string &className);

        virtual PrismMessage                *createMessageInstance                          (const UI32 &operationCode);

                ResourceId                   pqExecWrapper                                  (const string &sqlString, PGresult *&pPGresult, UI32 &numberOfResults);
                void                         freePqResultsWrapper                           (PGresult *&pPGresult);

                UI64                         getInstanceIdFromResult                        (PGresult *pPGresult, SI32 instanceIdColumnNumber, UI32 row);
                ObjectId                     getOidFromResult                               (PGresult *pPGresult, SI32 classIdColumnNumber, SI32 instanceIdColumnNumber, UI32 row);

                ResourceId                   loadWaveManagedObjects                         (const RecursiveQueryContext &recursiveQueryContext, const string &className, const string &sqlString, const vector<string> &selectFieldsInManagedObject, vector<WaveManagedObject *> &waveManagedObjectPointerResultVector);
                ResourceId                   loadObjectsForOidsFromATable                   (const RecursiveQueryContext &recursiveQueryContext, const UI32 &classId, const vector<UI64> &vectorOfInstanceIds, vector<WaveManagedObject *> &pWaveManagedObjectPointerVector);
                ResourceId                   queryAuxiliaryTableRowsForVectorOfOwnerOids    (const RecursiveQueryContext &recursiveQueryContext, const string &auxiliaryTableName, const UI32 &ownerClassId, const vector<UI64> &ownerInstanceIdVector, map <ObjectId, vector <ObjectId> > &ownerOidToVectorOfRelatedOidsMap);
                ResourceId                   getChildObjectsForACompositionRelation         (const RecursiveQueryContext &recursiveQueryContext, const string &auxiliaryTableName, const UI32& ownerClassId, const vector<UI64> &ownerInstanceIdVector, map <ObjectId, vector <WaveManagedObject *> > &ownerOidToVectorOfRelatedObjectsMap);

                ResourceId                   getCountFromDatabaseTableForAGivenSql          (const string &sqlString, UI32 &count, const string &className = "");
    protected :
    public :
                                             DatabaseObjectManagerExecuteQueryWorker (WaveObjectManager *pWaveObjectManager, bool isMultiDatabaseMode = false);
        virtual                             ~DatabaseObjectManagerExecuteQueryWorker ();

                void                         executeQueryMessageHandler              (DatabaseObjectManagerExecuteQueryMessage *pDatabaseObjectManagerExecuteQueryMessage);
                void                         executeQueryMessageHandlerForCount      (DatabaseObjectManagerExecuteQueryMessageForCount *pDatabaseObjectManagerExecuteQueryMessageForCount);
                WaveManagedObject           *loadWaveManagedObjectFromDatabase       (const ObjectId         &waveManagedObjectObjectId,  const string &schema, WaveObjectManager *pRequestingWaveObjectManager = NULL);
                vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabase      (const vector<ObjectId> &waveManagedObjectObjectIds, const string &schema, WaveObjectManager *pRequestingWaveObjectManager = NULL);
                vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabase      (const string &childClassName, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pRequestingWaveObjectManager = NULL);

                bool                         getIsMultiDatabaseMode                  () const;
                void                         setIsMultiDatabaseMode                  (const bool &isMultiDatabaseMode);

                void                         debugChangeQuerySettingsMessageHandler  (DatabaseObjectManagerDebugChangeQuerySettingsMessage *pDatabaseObjectManagerDebugChangeQuerySettingsMessage);
                void                         getDBSchemaInfoMessageHandler           (DatabaseObjectManagerGetDBSchemaInfoMessage *pDatabaseObjectManagerGetDBSchemaInfoMessage);
                void                         dropAllDbViewsMessageHandler            (DatabaseObjectManagerDropAllDBViewsMessage *pDatabaseObjectManagerDropAllDBViewsMessage);


    // Now the data members

    private :
        bool m_isMultiDatabaseMode;

    protected :
    public :
        friend class DatabaseObjectManager;
};

}

#endif // DATABASEOBJECTMANAGEREXECUTEQUERYWORKER_H
