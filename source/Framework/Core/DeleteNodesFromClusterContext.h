/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DELETENODESFROMCLUSTERCONTEXT_H
#define DELETENODESFROMCLUSTERCONTEXT_H

#include "Framework/Core/CreateClusterWithNodesContext.h"

namespace WaveNs
{

class DeleteNodesFromClusterContext : public CreateClusterWithNodesContext
{
    private :
    protected :
    public :
                            DeleteNodesFromClusterContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                            DeleteNodesFromClusterContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual            ~DeleteNodesFromClusterContext ();
                void        addLocationId                 (const LocationId &locationId);
                void        removeLocationId              (const LocationId &locationId);
                UI32        getNumberOfLocationIds        ();
                LocationId  getLocationIdAt               (const UI32 &i);
                bool        getIsConfigurationChange      () const;
                void        setIsConfigurationChange      (const bool isConfigurationChange);

    // Now the data members

    private :
                bool        m_isConfigurationChange;
    protected :
    public :
};

}

#endif // DELETENODESFROMCLUSTERCONTEXT_H
