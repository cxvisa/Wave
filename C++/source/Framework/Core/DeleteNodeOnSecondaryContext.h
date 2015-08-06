/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef DELETENODEONSECONDARYCONTEXT_H
#define DELETENODEONSECONDARYCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/Utils/PrismAsynchronousContext.h"
#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class DeleteNodeOnSecondaryContext : public PrismLinearSequencerContext
{
    private :

    protected :
    public :
                                DeleteNodeOnSecondaryContext   (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                DeleteNodeOnSecondaryContext   (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~DeleteNodeOnSecondaryContext   ();

        void                    addKnownLocationId             (const LocationId &locationId);
        vector<LocationId>      getKnownLocationId             ();
        bool                    getIsStartServiceIsRequired    () const;
        void                    setIsStartServiceIsRequired    (const bool &isStartServiceIsRequired);
    // Now the data members

    private :
        vector<LocationId>      m_KnownLocationIdsVector;
        bool                    m_IsStartServiceIsRequired;
    protected :
    public :
};

}

#endif
