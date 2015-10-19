/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEFAILOVERAGENTSEQUENCERCONTEXT_H
#define WAVEFAILOVERAGENTSEQUENCERCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class WaveFailoverAgentSequencerContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                    WaveFailoverAgentSequencerContext      (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                    WaveFailoverAgentSequencerContext      (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                    ~WaveFailoverAgentSequencerContext      ();

                void                setFailedLocationIds                    (const vector<LocationId> &failedLocationIds);
                vector<LocationId> &getFailedLocationIds                    ();

                void                setServiceToBeIgnored                   (const WaveServiceId &serviceToBeIgnored);
                WaveServiceId      getServiceToBeIgnored                   () const;
                
                void                setSecondaryNodeStatus                  (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status);
                void                updateSecondaryNodeStatus               (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort, ResourceId status);
                ResourceId          getSecondaryNodeStatus                  (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort);
                bool                isSecondaryNodeStatusSet                (const string &secondaryNodeIpAddress, const SI32 &secondaryNodePort);

                bool                getIsConfigurationChange                () const;
                void                setIsConfigurationChange                (const bool isConfigurationChange);

                void                setOlderPrimaryLocationId               (LocationId olderPrimary);
                LocationId          getOlderPrimaryLocationId               () const;
                bool                getIsPrincipalChangedWithThisFailover   () const;
                void                setIsPrincipalChangedWithThisFailover   (bool isPrincipalChangedWithThisFailover);
                void                setConnectedLocationVector              (const vector<LocationId> &connectedLocationIds);
                void                getConnectedLocationVector              (vector <LocationId> &connectedLocationdIds);
                void                setUnknownWaveNodeLocationIds           (const vector<LocationId> &failedLocationIds);
                vector<LocationId>  getUnknownWaveNodeLocationIds           (); 
                void                setAnyConfigurationChangeTrackingNumber (const UI64 &trackingNumber);
                UI64                getAnyConfigurationChangeTrackingNumber () const;

    // Now the data members

    private :
        vector<LocationId>      m_failedLocationIds;
        WaveServiceId          m_serviceToBeIgnored;
        map<string, ResourceId> m_secondaryNodesStatus;
        bool                    m_isConfigurationChange;
        LocationId              m_olderPrimaryLocationId;
        bool                    m_isPrincipalChangedWithThisFailover;
        vector<LocationId>      m_connectedLocationIds;
        vector<LocationId>      m_unknownWaveNodeLocationIds;
        UI64                    m_anyConfiguraitonChangeTrackingNumber;

    protected :
    public :
};

}

#endif // WAVEFAILOVERAGENTSEQUENCERCONTEXT_H 
