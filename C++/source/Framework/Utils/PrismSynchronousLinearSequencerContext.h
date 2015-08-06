/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author Vidyasagara Reddy Guntaka                                      *
 ***************************************************************************/

#ifndef PRISMSYNCHRONOUSLINEARSEQUENCERCONTEXT_H
#define PRISMSYNCHRONOUSLINEARSEQUENCERCONTEXT_H

#include "Framework/Types/Types.h"
#include "Framework/MultiThreading/PrismPosixThread.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveMessage;
class WaveElement;
class PrismSynchronousLinearSequencerContext;
class PrismAsynchronousContext;
class WaveManagedObject;

typedef ResourceId (WaveElement::* PrismSynchronousLinearSequencerStep) (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

class PrismSynchronousLinearSequencerContext
{
    private :
        void       advanceCurrentStep ();
        ResourceId executeCurrentStep ();
        void       garbageCollect     ();

    protected :
    public :
                                                        PrismSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                        PrismSynchronousLinearSequencerContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                        PrismSynchronousLinearSequencerContext (const PrismSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext);
        virtual                                        ~PrismSynchronousLinearSequencerContext ();
                PrismSynchronousLinearSequencerContext &operator =                             (const PrismSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext);
                ResourceId                              getCompletionStatus                    ();
                ResourceId                              execute                                ();
                WaveMessage                           *getPWaveMessage                       ();
                void                                    setPWaveMessage                       (WaveMessage *pWaveMessage);
                PrismAsynchronousContext               *getPPrismAsynchronousContext           ();
                bool                                    getIsTransactionStartedByMe            () const;
                void                                    setIsTransactionStartedByMe            (const bool &isTransactionStartedByMe);

                void                                    addManagedObjectsForGarbageCollection  (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection);
                void                                    addManagedObjectForGarbageCollection   (WaveManagedObject *pWaveManagedObjectForGarbageCollection);

                bool                                    getIsADelayedCommitTransaction         () const;
                void                                    setIsADelayedCommitTransaction         (const bool &isADelayedCommitTransaction);

    // Now the data  members

    private :
        WaveMessage                        *m_pWaveMessage;
        PrismAsynchronousContext            *m_pPrismAsynchronousContext;
        WaveElement                        *m_pWaveElement;
        PrismSynchronousLinearSequencerStep *m_pSteps;
        UI32                                 m_numberOfSteps;
        UI32                                 m_currentStep;
        ResourceId                           m_completionStatus;
        bool                                 m_isTransactionStartedByMe;

        vector<WaveManagedObject *>          m_managedObjectsForGarbageCollection;

        bool                                 m_isADelayedCommitTransaction;

        clockid_t                            m_clockId;

    protected :
    public:
};

}

#endif // PRISMSYNCHRONOUSLINEARSEQUENCERCONTEXT_H
