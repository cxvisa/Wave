/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMODELTESTCONTEXT_H
#define NETWORKMODELTESTCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Regression/RegressionTestMessage.h"
#include "Framework/Utils/WaveAsynchronousContext.h"

using namespace WaveNs;


namespace IsleNs
{

class NetworkModelTestContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                 NetworkModelTestContext (RegressionTestMessage   *pRegressionTestMessage,   WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                 NetworkModelTestContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);

        virtual ~NetworkModelTestContext ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // NETWORKMODELTESTCONTEXT_H
