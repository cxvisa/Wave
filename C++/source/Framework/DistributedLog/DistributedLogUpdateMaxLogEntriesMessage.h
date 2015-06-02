/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGUPDATEMAXLOGENTRIESMESSAGE_H
#define DISTRIBUTEDLOGUPDATEMAXLOGENTRIESMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class DistributedLogUpdateMaxLogEntriesMessage : public ManagementInterfaceMessage
{
    private :
        void               setupAttributesForSerialization  ();

    protected :
    public :
                           DistributedLogUpdateMaxLogEntriesMessage ();
                           DistributedLogUpdateMaxLogEntriesMessage (const UI32 &maxLogEntries);
        virtual           ~DistributedLogUpdateMaxLogEntriesMessage ();
                UI32       getMaxLogEntries                         () const;

    // Now the data members
    
    private :
        UI32    m_maxLogEntries;

    protected :
    public :
};

}

#endif // DISTRIBUTEDLOGUPDATEMAXLOGENTRIESMESSAGE_H
