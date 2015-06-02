/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
#define PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerExecuteTransactionMessage : public PrismMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                              PersistenceObjectManagerExecuteTransactionMessage (const string &sql);
                              PersistenceObjectManagerExecuteTransactionMessage ();
        virtual              ~PersistenceObjectManagerExecuteTransactionMessage ();

                const string &getSql                                            () const;
                      void    setSql                                            (const string &sql);

                void                setConfigNamesForInsert                   (const vector<string> &configNamesForInsert);
                vector<string>      getConfigNamesForInsert                   () const;
                void                setConfigValuesForInsert                  (const vector<string> &configValuesForInsert);
                vector<string>      getConfigValuesForInsert                  () const;
                void                setConfigTypesForInsert                   (const vector<ResourceId> &configTypesForInsert);
                vector<ResourceId>  getConfigTypesForInsert                   () const;

                void                setConfigNamesForUpdate                   (const vector<string> &configNamesForUpdate);
                vector<string>      getConfigNamesForUpdate                   () const;
                void                setConfigValuesForUpdate                  (const vector<string> &configValuesForUpdate);
                vector<string>      getConfigValuesForUpdate                  () const;
                void                setConfigTypesForUpdate                   (const vector<ResourceId> &configTypesForUpdate);
                vector<ResourceId>  getConfigTypesForUpdate                   () const;
    // Now the data members

    private :
        string             m_sql;
        vector<string>     m_configNamesForInsert;
        vector<string>     m_configValuesForInsert;
        vector<ResourceId> m_configTypesForInsert;

        vector<string>     m_configNamesForUpdate;
        vector<string>     m_configValuesForUpdate;
        vector<ResourceId> m_configTypesForUpdate;
    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONMESSAGE_H
