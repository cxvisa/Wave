/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETESTOBJECTMANAGER_H
#define WAVETESTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Regression/RegressionTestMessage.h"
#include "Regression/RegressionPrepareMessage.h"
#include "Regression/RegressionPrepareMessage2.h"
#include "Regression/RegressionTestPatternsMessage.h"

#include <map>
#include <vector>
#include <string>

namespace WaveNs
{

class WaveTestObjectManager : public WaveLocalObjectManager
{
    private :
        virtual WaveMessage *createMessageInstance (const UI32 &operationCode);

    protected :
                     WaveTestObjectManager               (const string &waveTestObjectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
        virtual void testRequestHandler                  (RegressionTestMessage *pMessage) = 0;
                void prepareForRegressionRequestHandler  (RegressionPrepareMessage *pMessage);
                void prepareForRegressionRequestHandler2 (RegressionPrepareMessage2 *pMessage);
              string getTestParameterValue               (const string &inputKeyString);

        virtual void runTestPatternsHandler              (RegressionTestPatternsMessage *pMessage);

    public :

    // Now the data members

    private :
    protected :
        map<string, string> m_testParameters;
        vector<string> m_regressionInput;

    public :
};

}

#endif // WAVETESTOBJECTMANAGER_H
