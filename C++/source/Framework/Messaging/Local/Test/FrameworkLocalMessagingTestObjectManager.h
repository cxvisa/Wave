/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER_H
#define FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER_H

#include "Regression/PrismTestObjectManager.h"

namespace WaveNs
{

class FrameworkTestabilityMessage1;
class FrameworkTestabilityMessage5;
class FrameworkTestabilityMessage6;
class FrameworkLocalMessagingTestContext;

class FrameworkLocalMessagingTestObjectManager : public PrismTestObjectManager
{
    private :
        FrameworkLocalMessagingTestObjectManager ();
    protected :
    public :
        virtual                                          ~FrameworkLocalMessagingTestObjectManager ();
        static  FrameworkLocalMessagingTestObjectManager *getInstance                              ();
        static  WaveServiceId                            getWaveServiceId                        ();
                void                                      testRequestHandler                       (RegressionTestMessage *pMessage);
                void                                      simpleAsynchronousMessageTestStep        (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      frameworkTestabilityMessage1Callback     (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage1 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleOneWayMessageTestStep              (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleSynchronousMessageTestStep         (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleRecallMessageTestStep              (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleRecallFromFrontMessageTestStep     (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleRecallFromBackMessageTestStep      (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      frameworkTestabilityMessage5Callback     (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage5 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      frameworkTestabilityMessage6Callback     (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage6 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                      simpleEventTestStep                      (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);

                WaveEvent                               *createEventInstance                      (const UI32 &eventOperationCode);

    // Now the data members

    private :
        static FrameworkLocalMessagingTestObjectManager *m_pFrameworkLocalMessagingTestObjectManager;

    protected :
    public:
};

}

#endif // FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER_H
