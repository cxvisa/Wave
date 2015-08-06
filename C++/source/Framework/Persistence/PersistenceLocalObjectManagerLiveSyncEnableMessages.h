/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERLIVESYNCENABLEMESSAGES_H
#define PERSISTENCELOCALOBJECTMANAGERLIVESYNCENABLEMESSAGES_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerGetLiveSyncEnableMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerGetLiveSyncEnableMessage ();
        virtual        ~PersistenceLocalObjectManagerGetLiveSyncEnableMessage ();
                bool    getIsLiveSyncEnabled                                  ();
                void    setIsLiveSyncEnabled                                  (const bool &isLiveSyncEnabled);

    // Now the data members

    private :
        bool m_isLiveSyncEnabled;

    protected :
    public :
};

class PersistenceLocalObjectManagerSetLiveSyncEnableMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerSetLiveSyncEnableMessage ();
                        PersistenceLocalObjectManagerSetLiveSyncEnableMessage (const bool &isLiveSyncEnabled);
        virtual        ~PersistenceLocalObjectManagerSetLiveSyncEnableMessage ();
                bool    getIsLiveSyncEnabled                                  ();
                void    setIsLiveSyncEnabled                                  (const bool &isLiveSyncEnabled);

    // Now the data members

    private :
        bool m_isLiveSyncEnabled;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERLIVESYNCENABLEMESSAGES_H
