/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERSETSTARTUPFILEMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERSETSTARTUPFILEMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerSetStartupFileMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerSetStartupFileMessage  (const ResourceId &startupFileType, const string &fileName);
                        PersistenceLocalObjectManagerSetStartupFileMessage  ();
        virtual        ~PersistenceLocalObjectManagerSetStartupFileMessage  ();

                string      getStartupFileName                                  () const;
                void        setStartupFileName                                  (const string &fileName);
                ResourceId  getStartupFileType                                  () const;
                void        setStartupFileType                                  (const ResourceId &startupFileType);

    // Now the data members

    private :
        ResourceId  m_startupFileType; 
        string      m_fileName;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERSETSTARTUPFILEMESSAGE_H
