/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAMESSAGE_H
#define DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "libpq-fe.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class DatabaseObjectManagerExecuteCopySchemaMessage : public PrismMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                              DatabaseObjectManagerExecuteCopySchemaMessage (const string &prepareString, const string &sourceSchema, const string &destSchema);
                                              DatabaseObjectManagerExecuteCopySchemaMessage (const string &sourceSchema, const string &destSchema);
                                              DatabaseObjectManagerExecuteCopySchemaMessage ();
        virtual                              ~DatabaseObjectManagerExecuteCopySchemaMessage ();

                string                        getClassName                                  () const;
                WaveObjectManager           *getPWaveObjectManager                          () const;
                void                         setPrepareString                               (const string &prepareString);
                string                       getPrepareString                               () const;
                void                         setPResults                                    (vector<WaveManagedObject *> *pResults);
                vector<WaveManagedObject *> *getPResults                                    () const;
                string                       getSourceSchema                                () const;
                void                         setSourceSchema                                (const string &sourceSchema);
                string                       getDestSchema                                  () const;
                void                         setDestSchema                                  (const string &destSchema);

    // Now the data members

    private :
        vector<WaveManagedObject *> *m_pResults;
        string                      m_prepareString;
        string                      m_sourceSchema;
        string                      m_destSchema;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREXECUTECOPYSCHEMAMESSAGE_H
