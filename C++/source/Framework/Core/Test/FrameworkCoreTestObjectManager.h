/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKCORETESTOBJECTMANAGER_H
#define FRAMEWORKCORETESTOBJECTMANAGER_H

#include "Regression/WaveTestObjectManager.h"

namespace WaveNs
{
extern vector<SI64> vectorSI64;
class FrameworkCoreTestObjectManager : public WaveTestObjectManager
{
    private :
                 FrameworkCoreTestObjectManager ();
	 void    initialize                     (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
    protected :
    public :
        virtual                                ~FrameworkCoreTestObjectManager                      ();
        static  FrameworkCoreTestObjectManager *getInstance                                         ();
        static  WaveServiceId                  getWaveServiceId                                   ();
                void                            testRequestHandler                                  (RegressionTestMessage *pMessage);
                void                            frameworkCoreTestFormattedErrorStringValidationStep (WaveLinearSequencerContext *pWaveLinearSequencerContext);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FRAMEWORKCORETESTOBJECTMANAGER_H
