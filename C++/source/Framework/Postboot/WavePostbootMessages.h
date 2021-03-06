/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTMESSAGES_H
#define WAVEPOSTBOOTMESSAGES_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class ExecutePostbootPassTableMessage : public WaveMessage
{
    private :
    protected :
    public :
                               ExecutePostbootPassTableMessage ();
        virtual               ~ExecutePostbootPassTableMessage ();

    // Now the data members
    private :
    protected :
    public :
};

}

#endif // WAVEPOSTBOOTMESSAGES_H
