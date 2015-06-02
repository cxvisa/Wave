/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef SLOTFAILOVERAGENT_H
#define SLOTFAILOVERAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class SlotFailoverAgentContext;

class SlotFailoverAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            SlotFailoverAgent                   (WaveObjectManager *pWaveObjectManager, UI32 slotNumber);
        virtual            ~SlotFailoverAgent                   ();
        virtual ResourceId  execute                             ();

                ResourceId  getListOfEnabledServicesStep        (SlotFailoverAgentContext *pSlotFailoverAgentContext);
                ResourceId  sendSlotFailoverStep                (SlotFailoverAgentContext *pSlotFailoverAgentContext);

                bool        requiresSlotFailoverNotification    (const PrismServiceId &prismServiceId);

    // Now the data members

    private :
                UI32        m_slotNumber;
    protected :
    public :
};

}

#endif // SlotFailoverAgent_H
