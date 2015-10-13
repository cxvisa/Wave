/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTAGENT_H
#define PRISMPOSTBOOTAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/PrismPostbootTypes.h"

namespace WaveNs
{

class PrismPostbootAgentContext;

class PrismPostbootAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            PrismPostbootAgent            (WaveObjectManager *pWaveObjectManager);
                            PrismPostbootAgent            (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, const UI32 &recoveryType);
        virtual            ~PrismPostbootAgent            ();

        virtual ResourceId  execute                       ();
                ResourceId  getListOfEnabledServicesStep  (PrismPostbootAgentContext *pPrismPostbootAgentContext);
                ResourceId  mergeStaticRegistrationsStep  (PrismPostbootAgentContext *pPrismPostbootAgentContext);
                ResourceId  notifyPostbootStartedStep       (PrismPostbootAgentContext *pPrismPostbootAgentContext);
                ResourceId  sendPostbootPassStep            (PrismPostbootAgentContext *pPrismPostbootAgentContext);
                ResourceId  notifyPostbootCompletedStep     (PrismPostbootAgentContext *pPrismPostbootAgentContext);
                bool        requiresPostboot              (const WaveServiceId &waveServiceId);

                void        printRegistrationTable        (void);
        static  void        populateRegistrations         (map <UI32, vector <postbootPass> > registrationsTable);

    // Now the data members

    private :
        // Global table for postboot registrations. The table resizes based on registrations
                map <UI32, vector <postbootPass> >        m_postbootTable;
                UI32        m_eventId;
                UI32        m_parameter;
                UI32        m_recoveryType;
    protected :
    public :
};

}

#endif // PRISMPOSTBOOTAGENT_H
