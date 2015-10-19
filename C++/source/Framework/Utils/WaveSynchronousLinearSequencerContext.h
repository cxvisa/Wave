/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author Vidyasagara Reddy Guntaka                                      *
 ***************************************************************************/

#ifndef WAVESYNCHRONOUSLINEARSEQUENCERCONTEXT_H
#define WAVESYNCHRONOUSLINEARSEQUENCERCONTEXT_H

#include "Framework/Types/Types.h"
#include "Framework/MultiThreading/WavePosixThread.h"

#include <vector>

using namespace std;

namespace WaveNs
{

class WaveMessage;
class WaveElement;
class WaveSynchronousLinearSequencerContext;
class WaveAsynchronousContext;
class WaveManagedObject;

typedef ResourceId (WaveElement::* WaveSynchronousLinearSequencerStep) (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

class WaveSynchronousLinearSequencerContext
{
    private :
        void       advanceCurrentStep ();
        ResourceId executeCurrentStep ();
        void       garbageCollect     ();

    protected :
    public :
                                                        WaveSynchronousLinearSequencerContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                        WaveSynchronousLinearSequencerContext (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                        WaveSynchronousLinearSequencerContext (const WaveSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext);
        virtual                                        ~WaveSynchronousLinearSequencerContext ();
                WaveSynchronousLinearSequencerContext &operator =                             (const WaveSynchronousLinearSequencerContext &prismSynchronousLinearSequencerContext);
                ResourceId                              getCompletionStatus                    ();
                ResourceId                              execute                                ();
                WaveMessage                           *getPWaveMessage                       ();
                void                                    setPWaveMessage                       (WaveMessage *pWaveMessage);
                WaveAsynchronousContext               *getPWaveAsynchronousContext           ();
                bool                                    getIsTransactionStartedByMe            () const;
                void                                    setIsTransactionStartedByMe            (const bool &isTransactionStartedByMe);

                void                                    addManagedObjectsForGarbageCollection  (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection);
                void                                    addManagedObjectForGarbageCollection   (WaveManagedObject *pWaveManagedObjectForGarbageCollection);

                bool                                    getIsADelayedCommitTransaction         () const;
                void                                    setIsADelayedCommitTransaction         (const bool &isADelayedCommitTransaction);

    // Now the data  members

    private :
        WaveMessage                        *m_pWaveMessage;
        WaveAsynchronousContext            *m_pWaveAsynchronousContext;
        WaveElement                        *m_pWaveElement;
        WaveSynchronousLinearSequencerStep *m_pSteps;
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

#endif // WAVESYNCHRONOUSLINEARSEQUENCERCONTEXT_H
