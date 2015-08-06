/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGERDROPALLDBVIEWSMESSAGE_H
#define DATABASEOBJECTMANAGERDROPALLDBVIEWSMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class DatabaseObjectManagerDropAllDBViewsMessage : public WaveMessage
{
    private :
    protected :
    public :
                                             DatabaseObjectManagerDropAllDBViewsMessage ();
        virtual                             ~DatabaseObjectManagerDropAllDBViewsMessage ();

    // Now the data members

    private :

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGERDROPALLDBVIEWSMESSAGE_H
