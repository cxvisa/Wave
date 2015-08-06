/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                
 *   All rights reserved.  
 *   Description: This file defines the configuration intent repository
 *                which stores configuration intents as serialized messages.
 *                A configuration intent can be categorized as any plug-in
 *                handled message that triggers hardware programming and a
 *                change in the wave configuration database.  These
 *                configuration intents are temporarily stored on the HA Peer
 *                and used to replay the last configuration if there is an
 *                HA failover while a configuration was in progress.  The
 *                configuration intents are intercepted and stored on the
 *                HA peer prior to the plug-in handling the message and
 *                removed from the HA peer once the configuration has 
 *                completed processing from the plug-in.
 *
 *   Author : Brian Adaniya 
 *   Date   : 10/23/2012                                           
 ***************************************************************************/

#ifndef WAVECONFIGURATIONINTENTREPOSITORY_H
#define WAVECONFIGURATIONINTENTREPOSITORY_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveMutex.h"
#include <vector>
#include <map>

namespace WaveNs
{

class WaveConfigurationIntentRepository
{
    private :
    protected :
    public :                        
        static  void                                addConfigurationIntent                  (const UI32 &configurationIntentMessageId, const string &configurationIntentSerializedMessage);
        static  string                              getConfigurationIntent                  (const UI32 &configurationIntentMessageId);
        static  string                              getLastConfigurationIntent              ();
        static  void                                removeConfigurationIntent               (const UI32 &configurationIntentMessageId);
        static  string                              getAndRemoveConfigurationIntent         (const UI32 &configurationIntentMessageId);
        static  void                                clearConfigurationIntentRepository      ();
        static  UI32                                getConfigurationIntentRepositorySize    ();
        static  void                                getConfigurationIntentRepository        (vector<UI32> &configurationIntentRepositoryVector, map<UI32, string> &configurationIntentRepositoryMap);
        
    // Now the data members

    private :
        static  vector <UI32>                       s_waveConfigurationIntentRepositoryVector;
        static  map <UI32, string>                  s_waveConfigurationIntentRepositoryMap;
        static  WaveMutex                          s_waveConfigurationIntentRepositoryMutex;

    protected :
    public :
};

}

#endif // WAVECONFIGURATIONINTENTREPOSITORY_H

