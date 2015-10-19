/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVESENDMULTICASTCONTEXT_H
#define WAVESENDMULTICASTCONTEXT_H

#include "Framework/Utils/WaveAsynchronousContext.h"

#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class WaveMessage;

class WaveSendMulticastContext : public WaveAsynchronousContext
{
    private:
    protected:
    public:
                                            WaveSendMulticastContext (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                            ~WaveSendMulticastContext ();
                void                        setWaveMessage          (WaveMessage *pWaveMessage);
                WaveMessage*               getWaveMessage          ();
                vector<LocationId>          getAllLocationsToSent    () const;
                void                        setAllLocationsToSent    (vector<LocationId> &locationIds);
                ResourceId                  getStatusForALocation    (LocationId &loctionId);
                void                        setStatusForALocation    (LocationId &locationId, ResourceId &locationStatus);
       
                ResourceId                  getOverallMulticastStatus ();
                void                        setMulticastStatus        (ResourceId &status);
    // Data Members
    private:
        WaveMessage                   *m_pWaveMessage;
        vector<LocationId>              m_connectedLocationIds;
        map<LocationId, ResourceId>     m_locationStatus;
        ResourceId                      m_multicastStatus;
 
    protected:
    public:
};

}

#endif // WAVESENDMULTICASTCONTEXT_H

