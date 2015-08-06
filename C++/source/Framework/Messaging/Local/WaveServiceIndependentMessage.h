/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file defines the service independent message 
 *                class.  Service independent messages allow for immediate 
 *                handling of the message across any transport (Client,
 *                HaPeer, InterLocation).
 *   Author : Brian Adaniya 
 *   Date   : 10/18/2012                                           
 ***************************************************************************/

#ifndef WAVESERVICEINDEPENDENTMESSAGE_H
#define WAVESERVICEINDEPENDENTMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"
#include "Framework/Messaging/Local/WaveServiceIndependentMessageBase.h"

namespace WaveNs
{

class WaveServiceIndependentMessage : public WaveMessage, public WaveServiceIndependentMessageBase
{
    private :
    protected :
        virtual void            setupAttributesForSerialization ();

    public :
                                WaveServiceIndependentMessage   (WaveServiceId serviceCode, UI32 operationCode);
        virtual                ~WaveServiceIndependentMessage   ();


    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESERVICEINDEPENDENTMESSAGE_H
