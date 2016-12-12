/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONTESTOBJECTMANAGER_H
#define REGRESSIONTESTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Regression/RegressionTestEntry.h"
#include <vector>

namespace WaveNs
{

class RegressionTestObjectManagerGetTestServiceEntriesMessage;
class RegressionTestObjectManagerSetTestServiceStateMessage;
class RegressionTestObjectManagerStartRegressionMessage;
class RegressionTestObjectManagerPrepareTestForAServiceMessage;
class RegressionTestObjectManagerRunTestForAServiceMessage;
class RegressionTestObjectManagerRunTestPatternsForAServiceMessage;

class RegressionTestObjectManager : public WaveLocalObjectManager
{
    private :
                              RegressionTestObjectManager           ();
                void          getTestServiceEntriesMessageHandler   (RegressionTestObjectManagerGetTestServiceEntriesMessage      *pMessage);
                void          setTestServiceStateMessageHandler     (RegressionTestObjectManagerSetTestServiceStateMessage        *pMessage);
                void          startRegressionMessageHandler         (RegressionTestObjectManagerStartRegressionMessage            *pMessage);
                void          prepareAServiceTestMessageHandler     (RegressionTestObjectManagerPrepareTestForAServiceMessage     *pMessage);
                void          runAServiceTestMessageHandler         (RegressionTestObjectManagerRunTestForAServiceMessage         *pMessage);
                void          runAServiceTestPatternsMessageHandler (RegressionTestObjectManagerRunTestPatternsForAServiceMessage *pMessage);

        virtual WaveMessage *createMessageInstance               (const UI32 &operationCode);

    protected :
    public :
        static RegressionTestObjectManager *getInstance          ();
        static WaveServiceId                getWaveServiceId     ();
        static string                       getServiceName       ();

        static void                         addToRegressionShell (const WaveServiceId &waveServiceId, const bool &isEnabledByDefault);

    // Now the data members

    private :
        vector<RegressionTestEntry> m_testServiceEntries;

    protected :
    public :

    friend class RegressionTestThread;
};

}

#endif //REGRESSIONTESTOBJECTMANAGER_H
