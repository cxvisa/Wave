/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERCOPYSCHEMAMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERCOPYSCHEMAMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerCopySchemaMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerCopySchemaMessage (const string &sourceSchema, const string &destSchema);
                        PersistenceLocalObjectManagerCopySchemaMessage ();
        virtual        ~PersistenceLocalObjectManagerCopySchemaMessage ();

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

#endif // PERSISTENCELOCALOBJECTMANAGERCOPYSCHEMAMESSAGE_H
