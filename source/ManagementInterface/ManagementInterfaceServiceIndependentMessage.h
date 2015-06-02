/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author :  Anand Subramanian                                           *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACESERVICEINDEPENDENTMESSAGE_H
#define MANAGEMENTINTERFACESERVICEINDEPENDENTMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "Framework/Messaging/Local/WaveServiceIndependentMessageBase.h"

namespace WaveNs
{

class ManagementInterfaceServiceIndependentMessage : public ManagementInterfaceMessage, public WaveServiceIndependentMessageBase
{
    private :
    protected :        
        void            setupAttributesForSerialization ();

    public :
                        ManagementInterfaceServiceIndependentMessage (const string &serviceName, const UI32 &operationId);
        virtual        ~ManagementInterfaceServiceIndependentMessage ();

    // Now the data members

    private :
    protected :
    public :

};

}

#endif // MANAGEMENTINTERFACESERVICEINDEPENDENTMESSAGE_H
