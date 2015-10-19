/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEDEBUGINFORMATIONCONTEXT_H
#define WAVEDEBUGINFORMATIONCONTEXT_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class WaveDebugInformationContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                            WaveDebugInformationContext             (WaveMessage* pWaveMessage, WaveElement* pWaveElement, WaveLinearSequencerStep* pSteps, UI32 numberOfSteps);
        virtual                            ~WaveDebugInformationContext             ();

                void                        setDebugInformation                     (const string &debugInformation);  
                void                        appendDebugInformation                  (const string &debugInformation);  
                const   string &            getDebugInformation                     () const;  

        // Now the data members

    private :
                        string              m_debugInformation;

    protected :
    public :
};

}
#endif // WAVEDEBUGINFORMATIONCONTEXT_H

