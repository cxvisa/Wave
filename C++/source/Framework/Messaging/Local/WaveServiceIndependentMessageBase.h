/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file defines the service independent message base
 *                class.  Service independent messages allow for immediate 
 *                handling of the message across any transport (Client,
 *                HaPeer, InterLocation).
 *   Author : Brian Adaniya 
 *   Date   : 10/18/2012                                           
 ***************************************************************************/

#ifndef WAVESERVICEINDEPENDENTMESSAGEBASE_H
#define WAVESERVICEINDEPENDENTMESSAGEBASE_H

namespace WaveNs
{

class WaveServiceIndependentMessageBase
{
    private :
    protected :
    public :
                                WaveServiceIndependentMessageBase ();
        virtual                ~WaveServiceIndependentMessageBase ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESERVICEINDEPENDENTMESSAGEBASE_H
