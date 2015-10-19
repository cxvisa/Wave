/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTAGENT_H
#define WAVEPOSTBOOTAGENT_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Postboot/WavePostbootTypes.h"

namespace WaveNs
{

class WavePostbootAgentContext;

class WavePostbootAgent : protected WaveWorker
{
    private :
    protected :
    public :
                            WavePostbootAgent            (WaveObjectManager *pWaveObjectManager);
                            WavePostbootAgent            (WaveObjectManager *pWaveObjectManager, const UI32 &event, const UI32 &parameter, const UI32 &recoveryType);
        virtual            ~WavePostbootAgent            ();

        virtual ResourceId  execute                       ();
                ResourceId  getListOfEnabledServicesStep  (WavePostbootAgentContext *pWavePostbootAgentContext);
                ResourceId  mergeStaticRegistrationsStep  (WavePostbootAgentContext *pWavePostbootAgentContext);
                ResourceId  notifyPostbootStartedStep       (WavePostbootAgentContext *pWavePostbootAgentContext);
                ResourceId  sendPostbootPassStep            (WavePostbootAgentContext *pWavePostbootAgentContext);
                ResourceId  notifyPostbootCompletedStep     (WavePostbootAgentContext *pWavePostbootAgentContext);
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

#endif // WAVEPOSTBOOTAGENT_H
