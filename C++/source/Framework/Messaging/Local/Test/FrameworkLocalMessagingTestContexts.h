/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKLOCALMESSAGINGTESTCONTEXTS_H
#define FRAMEWORKLOCALMESSAGINGTESTCONTEXTS_H

#include "Framework/Utils/PrismLinearSequencerContext.h"

namespace WaveNs
{

class FrameworkLocalMessagingTestContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                    FrameworkLocalMessagingTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
                   ~FrameworkLocalMessagingTestContext ();

        LocationId  getRemoteLocationId                ();
        void        setRemoteLocationId                (const LocationId &remoteLocationId);

        void        setNumberOfMessagesToSend          (const UI32 &numberOfMessagesToSend);
        UI32        getNumberOfMessagesToSend          ();

        void        incrementNumberOfMessagesSend      ();
        void        resetNumberOfMessagesSend          ();
        UI32        getNumberOfMessagesSend            ();

        bool        areAllMessagesSent                 ();
    // Now the data members

    private :
        LocationId m_remoteLocationId;
        UI32       m_numberOfMessagesToSend;
        UI32       m_numberOfMessagesSend;

    protected :
    public :
};

}

#endif // FRAMEWORKLOCALMESSAGINGTESTCONTEXTS_H
