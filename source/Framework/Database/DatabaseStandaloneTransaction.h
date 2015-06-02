/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mayur Mahajan                                                *
 ***************************************************************************/

#ifndef DATABASESTANDALONETRANSACTION_H
#define DATABASESTANDALONETRANSACTION_H

#include "Framework/Types/Types.h"
#include "Framework/Database/DatabaseConnection.h"
#include "Framework/ObjectRelationalMapping/DatabaseSchema.h"
#include "Framework/Core/PrismFrameworkConfiguration.h"

#include <string>

using namespace std;

namespace WaveNs
{

class DatabaseStandaloneTransaction
{
    private :
               bool         executeStep                  (const string &sql);

               void         bootDatabaseStep                ();
               PGconn       *getDatabaseConnection       ();
               ResourceId   getTableNamesForWaveSchema      (vector<string>& tableNames);

    protected :
    public :
                            DatabaseStandaloneTransaction   ();
                           ~DatabaseStandaloneTransaction   ();
               bool         execute                         (const string &sql);
               bool         getObjectInstanceIdsForTable    (const string &tableName, vector<UI64>& objectInstanceIds);
               bool         checkIfTableHasEntriesInDb      (const string &tableName, const string &schema, bool &exists);                                                       
               UI32         getSchemaChangeInfo             (DatabaseSchema &databaseSchema);
//               void         populateSchemaUpgradeTableInDb  ();  
//               UI32         getTableIdsFromUpgradeMO        (vector<pair<string, UI32> > &tableIdsFromUpgradeMO);
               void         establishDbConnection           ();
               void         shutdownDatabase                ();
               ResourceId   rollbackDatabase                (); 
               ResourceId   rollbackConfigFile              (PrismFrameworkConfiguration& prismFrameworkConfiguration);
               ResourceId   dropAllDBViews                  ();

    // Now the data members

    private :
            bool            m_needConnectionTeardown;
            UI8             m_bootCount;
	static  PrismMutex      s_standaloneTransactionMutex;
    protected :
    public :
};

}

#endif // DATABASESTANDALONETRANSACTION_H
