/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPDATELISTOFSECONDARIESCONTEXT_H
#define UPDATELISTOFSECONDARIESCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class UpdateListOfSecondariesContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                            UpdateListOfSecondariesContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                            UpdateListOfSecondariesContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual            ~UpdateListOfSecondariesContext ();
                void        addSecondaryNodeDetails        (const LocationId &locationId, const string &ipAddress, const UI32 &port, bool isNodeNew);
                void        setIsThisNodeNew               (bool thisNodeNew);
                UI32        getNumberOfSecondaryLocations  () const;
                LocationId  getLocationIdAtIndex           (const UI32 &index) const;
                string      getIpAddressAtIndex            (const UI32 &index) const;
                UI32        getPortAtIndex                 (const UI32 &index) const;
                bool        isNodeNewAtIndex               (const UI32 &index) const;
                bool        isThisNodeNew                  ()                  const;
                void        setConnectedLocationsAtPrimary (vector<LocationId> &locationIds);
                void        getConnectedLocationsAtPrimary (vector<LocationId> &locationIds);
    // Now the data members

    private :
        vector<LocationId> m_locationIdsForSecondaryNodes;
        vector<string>     m_IpAddressesForSecondaryNodes;
        vector<UI32>       m_portsForSecondaryNodes;
        vector<bool>       m_isNodeNewlyAdded;
        bool               m_isThisNodeNew;
        vector<LocationId> m_connectedLocationsAtPrimary;

    protected :
    public :
};

}

#endif // UPDATELISTOFSECONDARIESCONTEXT_H
