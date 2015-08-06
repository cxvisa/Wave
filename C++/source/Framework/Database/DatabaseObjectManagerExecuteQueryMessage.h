/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGE_H
#define DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "libpq-fe.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class DatabaseObjectManagerExecuteQueryMessage : public PrismMessage
{
    private :
    protected :
    public :
                                             DatabaseObjectManagerExecuteQueryMessage (const string &className, WaveObjectManager *pWaveObjectManager, const string &sql, const string &schema);
        virtual                             ~DatabaseObjectManagerExecuteQueryMessage ();

                string                       getClassName                             () const;
                WaveObjectManager           *getPWaveObjectManager                    () const;
                string                       getSql                                   () const;
                string                       getSchema                                () const;
                bool                         getLoadOneToManyRelationships            () const;
                void                         setLoadOneToManyRelationships            (const bool &loadOneToManyRelationships);
                bool                         getLoadCompositions                      () const;
                void                         setLoadCompositions                      (const bool loadCompositions);
                vector<string>               getSelectFields                          () const;
                void                         setSelectFields                          (const vector<string> &selectFields);
                vector<string>               getSelectFieldsInManagedObject           () const;
                void                         setSelectFieldsInManagedObject           (const vector<string> &selectFieldsInManagedObject);
                void                         setPResults                              (vector<WaveManagedObject *> *pResults);
                vector<WaveManagedObject *> *getPResults                              () const;

        static  void                         setDatabaseObjectManagerServiceId        (const WaveServiceId &databaseObjectManagerServiceId);
        static  WaveServiceId               getDatabaseObjectManagerServiceId        ();

    // Now the data members

    private :
               string                       m_className;
               WaveObjectManager           *m_pWaveObjectManager;
               string                       m_sql;
               string                       m_schema;
               vector<string>               m_selectFields;
               vector<string>               m_selectFieldsInManagedObject;
               bool                         m_loadOneToManyRelationships;
               bool                         m_loadCompositions;
               vector<WaveManagedObject *> *m_pResults;

        static WaveServiceId               m_databaseObjectManagerServiceId;

    protected :
    public :
};


class DatabaseObjectManagerDebugChangeQuerySettingsMessage : public ManagementInterfaceMessage
{
    private:
        void    setupAttributesForSerialization                         ();

    public:
                DatabaseObjectManagerDebugChangeQuerySettingsMessage    (const bool &useRecursiveQuery, const UI32 &batchSize);
                DatabaseObjectManagerDebugChangeQuerySettingsMessage    ();
               ~DatabaseObjectManagerDebugChangeQuerySettingsMessage    ();

        bool    getUseRecursiveQuery                                    () const;
        UI32    getBatchSize                                            () const;

    // Now the data members

    private :

        bool    m_useRecursiveQuery;
        UI32    m_batchSize;
};

}

#endif // DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGE_H
