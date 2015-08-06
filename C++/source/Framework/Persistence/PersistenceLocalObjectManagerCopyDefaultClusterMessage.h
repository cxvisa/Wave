/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Description : This is a dummy message created to do copy default to   *
 *                 startup in a cluster.                                   *  
 *   Author : Anil ChannaveeraSetty                                        *
 *   Date : Oct/05/2010                                                    *     
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERCOPYDEFAULTCLUSTERMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERCOPYDEFAULTCLUSTERMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace std;

namespace WaveNs
{

    class PersistenceLocalObjectManagerCopyDefaultClusterMessage : public WaveMessage
    { 

        public :

                    PersistenceLocalObjectManagerCopyDefaultClusterMessage ();
                   ~PersistenceLocalObjectManagerCopyDefaultClusterMessage (); 
            
    };

}

#endif // PERSISTENCELOCALOBJECTMANAGERCOPYDEFAULTCLUSTERMESSAGE_H
