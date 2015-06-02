/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKREMOTEMESSAGINGTESTOBJECTMANAGER2_H
#define FRAMEWORKREMOTEMESSAGINGTESTOBJECTMANAGER2_H

#include "Regression/PrismTestObjectManager.h"

namespace WaveNs
{

class FrameworkTestabilityMessage1;
class FrameworkTestabilityMessage3;
class FrameworkTestabilityMessage4;
class FrameworkLocalMessagingTestContext;

class FrameworkRemoteMessagingTestObjectManager2 : public PrismTestObjectManager
{
    private :
        FrameworkRemoteMessagingTestObjectManager2 ();

    protected :
    public :
        virtual                                           ~FrameworkRemoteMessagingTestObjectManager2   ();
        static  FrameworkRemoteMessagingTestObjectManager2 *getInstance                                 ();
        static  PrismServiceId                             getPrismServiceId                           ();
                void                                       testRequestHandler                          (RegressionTestMessage *pMessage);
                void                                       selectARemoteLocationStep                   (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       simpleAsynchronousMessageTestStep           (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       simpleOneWayMessageTestStep                 (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       frameworkTestabilityMessage1Callback        (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage1 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       simpleSynchronousMessageTestStep            (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       asynchronousMessageWithBuffersTestStep      (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       asynchronousMessageWithBuffersCallback      (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage3 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       synchronousMessageWithBuffersTestStep       (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       asynchronousMessageWithLargeBuffersTestStep (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       synchronousMessageWithLargeBuffersTestStep  (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       asynchronousMessageAttributeTest            (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       asynchronousMessageAttributeTestCallback    (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage4 *pMessage, FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       synchronousMessageAttributeTest             (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       messageCloningTestStep                      (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);
                void                                       messageCloningWithBuffersTestStep           (FrameworkLocalMessagingTestContext *pFrameworkLocalMessagingTestContext);

    // Now the data members

    private :
        time_t  m_startTime;
        time_t  m_endTime;
        UI32    m_numberOfMessagesToSend;
    protected :
    public :
};

}

#endif // FRAMEWORKREMOTEMESSAGINGTESTOBJECTMANAGER2_H
