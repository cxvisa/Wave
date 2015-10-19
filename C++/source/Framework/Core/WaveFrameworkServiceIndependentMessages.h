/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file defines the wave framework service independent
 *                messages.  These service independent messages are directly
 *                handled in the HaPeerMessageReceiverThread or 
 *                InterLocationMessageReceiverThread.
 *   Author : Brian Adaniya 
 *   Date   : 10/22/2012                                           
 ***************************************************************************/

#ifndef WAVEFRAMEWORKSERVICEINDEPENDENTMESSAGES_H
#define WAVEFRAMEWORKSERVICEINDEPENDENTMESSAGES_H

#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"

namespace WaveNs
{

typedef enum
{
    SERIALIZED_CONFIGURATION_INTENT_BUFFER = 1
} FrameworkObjectManagerConfigurationIntentBufferId;

class FrameworkObjectManagerStoreConfigurationIntentMessage : public WaveServiceIndependentMessage
{
    private :
    protected :
                void            setupAttributesForSerialization                         ();

    public :
                                FrameworkObjectManagerStoreConfigurationIntentMessage   ();
                                FrameworkObjectManagerStoreConfigurationIntentMessage   (const UI32 &configurationIntentMessageId);
        virtual                ~FrameworkObjectManagerStoreConfigurationIntentMessage   ();

                UI32            getConfigurationIntentMessageId                         () const;
                void            setConfigurationIntentMessageId                         (const UI32 &configurationIntentMessageId);

    // Now the data members
    
    private :
                UI32            m_configurationIntentMessageId;

    protected :
    public :
        
};

class FrameworkObjectManagerRemoveConfigurationIntentMessage : public WaveServiceIndependentMessage
{
    private :
    protected :
                void            setupAttributesForSerialization                         ();

    public :
                                FrameworkObjectManagerRemoveConfigurationIntentMessage  ();
                                FrameworkObjectManagerRemoveConfigurationIntentMessage  (const UI32 &configurationIntentMessageId);
        virtual                ~FrameworkObjectManagerRemoveConfigurationIntentMessage  ();

                UI32            getConfigurationIntentMessageId                         () const;
                void            setConfigurationIntentMessageId                         (const UI32 &configurationIntentMessageId);

    // Now the data members

    private :
                UI32            m_configurationIntentMessageId;

    protected :
    public :

};

}

#endif // WAVEFRAMEWORKSERVICEINDEPENDENTMESSAGES_H
