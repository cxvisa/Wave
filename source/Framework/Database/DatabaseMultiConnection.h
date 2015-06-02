/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEMULTICONNECTION_H
#define DATABASEMULTICONNECTION_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <string>
#include <map>
#include <set>

#include "libpq-fe.h"

using namespace std;

namespace WaveNs
{

class DatabaseMultiConnection
{
    private :
                    DatabaseMultiConnection ();

        static void lock                    ();
        static void unlock                  ();

    protected :
    public :
                                       ~DatabaseMultiConnection              ();

        static DatabaseMultiConnection *getInstance                          ();
        static void                     deleteInstance                       ();

               void                     connect                              (const UI32 &maximumNumberOfRetries);
               bool                     connect                              (const string &serverName, const UI32 &maximumNumberOfRetries);
               void                     close                                ();
               void                     close                                (const string &serverName);

               bool                     isAKnownServer                       (const string &serverName);
               bool                     isAConnectedServer                   (const string &serverName);
               PGconn                  *getServerConnection                  (const string &serverName);
               void                     addServer                            (const string &serverName, const string &serverDatabaseName, const UI32 &serverPort);
               void                     getServerDetails                     (const string &serverName,       string &serverDatabaseName,       UI32 &serverPort);

               bool                     isAKnownManagedObjectName            (const string &managedObject) const;
               void                     addManagedObjectToServerNameMapEntry (const string &managedObject, const string &serverName);
               string                   getServerNameForManagedObject        (const string &managedObject) const;

               PGconn                  *getServerConnectionForManagedObject  (const string &managedObject);

    // Now the data members

    private :
                     vector<string>           m_serverNames;
                     set<string>              m_serverSet;
                     map<string, string>      m_serverDatabaseNameMap;
                     map<string, UI32>        m_serverPortMap;
                     map<string, PGconn *>    m_serverConnectionMap;

                     map<string, string>      m_managedObjectToServerNameMap;

        static       PrismMutex               m_mutex;
        static       DatabaseMultiConnection *m_pDatabaseMultiConnection;
        static const UI32                     m_maximumNumOfRetriesWhenDBIsBusy;

    protected :
    public :
};

}

#endif // DATABASEMULTICONNECTION_H
