/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGUPDATELOGIDMESSAGE_H
#define DISTRIBUTEDLOGUPDATELOGIDMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class DistributedLogUpdateLogIdMessage : public ManagementInterfaceMessage
{
    private :
        void                    setupAttributesForSerialization  (); 

    protected :
    public :
                                DistributedLogUpdateLogIdMessage (); 
        virtual                ~DistributedLogUpdateLogIdMessage ();

    // Data Member
    private:
    protected:
    public:
};

}

#endif //DISTRIBUTEDLOGUPDATELOGIDMESSAGE_H

        
