/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERCOPYSCHEMAMESSAGE_H
#define PERSISTENCEOBJECTMANAGERCOPYSCHEMAMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerCopySchemaMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceObjectManagerCopySchemaMessage (const string &sourceSchema, const string &destSchema);
                        PersistenceObjectManagerCopySchemaMessage ();
        virtual        ~PersistenceObjectManagerCopySchemaMessage ();

                void    setSourceSchema                                   (const string &sourceSchema);
                string  getSourceSchema                                   () const;
                void    setDestSchema                                     (const string &destSchema);
                string  getDestSchema                                     () const;

    // Now the data members

    private :
        string m_sourceSchema;
        string m_destSchema;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERCOPYSCHEMAMESSAGE_H
