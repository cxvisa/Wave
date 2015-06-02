/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/PrismMutex.h"

#include <string>

#include "libpq-fe.h"

using namespace std;

namespace WaveNs
{

class DatabaseConnection
{
    private :
             DatabaseConnection (const string &name, const UI32 &port);

        void lock               ();
        void unlock             ();

    protected :
    public :
                                  ~DatabaseConnection ();

        static DatabaseConnection *getInstance        (const string &name, const UI32 &port);
        static void                deleteInstance     ();

               bool                connect            (const UI32 &maximumNumberOfRetries);
               void                close              ();

               PGconn             *getPConnection     ();

    // Now the data members

    private :
                string              m_name;
                UI32                m_port;
                PGconn              *m_pConnection;
                PrismMutex          m_mutex;

        static  DatabaseConnection *s_pDatabaseConnection; // Singleton connection object

    protected :
    public :
};

}

#endif // DATABASECONNECTION_H
