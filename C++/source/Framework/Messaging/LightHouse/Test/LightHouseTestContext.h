/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTHOUSETESTCONTEXT_H
#define LIGHTHOUSETESTCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

using WaveNs::WaveLinearSequencerContext;

namespace WaveNs
{

class LightHouseTestContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 LightHouseTestContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual ~LightHouseTestContext ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // LIGHTHOUSETESTCONTEXT_H
