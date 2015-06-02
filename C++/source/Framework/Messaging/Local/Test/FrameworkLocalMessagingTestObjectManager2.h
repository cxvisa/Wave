/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER2
#define FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER2

#include "Regression/PrismTestObjectManager.h"

namespace WaveNs
{

class FrameworkLocalMessagingTestContext;
class FrameworkTestabilityMessage1;
class FrameworkTestabilityMessage2;
class FrameworkTestabilityMessage7;

class FrameworkLocalMessagingTestObjectManager2 : public PrismTestObjectManager
{
    private :
                     FrameworkLocalMessagingTestObjectManager2                     ();
        virtual void testRequestHandler                                            (RegressionTestMessage *pRegressionTestMessage);
                void simpleAsynchronousMessageWithTimeoutTestStep                  (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void frameworkTestabilityMessage1Callback                          (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage1 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void simpleAsynchronousMessageWithBuffersWithTimeoutTestStep       (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void simpleAsynchronousMessageResponseDeliveryAfterTimeoutTestStep (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void frameworkTestabilityMessage2Callback                          (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage2 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void simpleAsynchronousMessageWithTimeout2TestStep                 (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void frameworkTestabilityMessage7Callback                          (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage7 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void simpleAsynchronousMessageWithBuffersWithTimeout2TestStep      (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void frameworkTestabilityMessage7Callback2                         (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage7 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);

    protected :
    public :
        virtual                                           ~FrameworkLocalMessagingTestObjectManager2 ();
        static  FrameworkLocalMessagingTestObjectManager2 *getInstance                               ();
        static  PrismServiceId                             getPrismServiceId                         ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FRAMEWORKLOCALMESSAGINGTESTOBJECTMANAGER2
