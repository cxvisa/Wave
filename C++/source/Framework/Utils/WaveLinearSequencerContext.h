/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVELINEARSEQUENCERCONTEXT_H
#define WAVELINEARSEQUENCERCONTEXT_H

#include "Framework/Types/Types.h"

#include <vector>

#include <pthread.h>

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

namespace WaveNs
{

class WaveMessage;
class WaveElement;
class WaveLinearSequencerContext;
class WaveAsynchronousContext;
class WaveManagedObject;

typedef void (WaveElement::* WaveLinearSequencerStep) (WaveLinearSequencerContext *pWaveLinearSequencerContext);

class WaveLinearSequencerContext
{
    private :
        void advanceCurrentStep ();
        void executeCurrentStep ();

        void garbageCollect     ();

    protected :
    public :
                                             WaveLinearSequencerContext                   (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                             WaveLinearSequencerContext                   (WaveAsynchronousContext *pWaveAsynchronousContext, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                             WaveLinearSequencerContext                   (const WaveLinearSequencerContext &waveLinearSequencerContext);
        virtual                             ~WaveLinearSequencerContext                   ();
                WaveLinearSequencerContext &operator =                                    (const WaveLinearSequencerContext &waveLinearSequencerContext);
                ResourceId                   getCompletionStatus                           ();
                void                         start                                         ();
                void                         executeNextStep                               (const ResourceId &currentStepStatus);
                void                         executeSuccessStep                            ();
                WaveMessage                *getPWaveMessage                              ();
                void                         setPWaveMessage                              (WaveMessage *pWaveMessage);
                WaveAsynchronousContext    *getPWaveAsynchronousContext                  ();
                WaveLinearSequencerContext &operator ++                                   ();
                WaveLinearSequencerContext &operator --                                   ();
                UI32                         getNumberOfCallbacksBeforeAdvancingToNextStep ();
                void                         holdAll                                       ();
                void                         unholdAll                                     ();
                bool                         getIsHoldAllRequested                         ();
                bool                         getIsTransactionStartedByMe                   () const;
                void                         setIsTransactionStartedByMe                   (const bool &isTransactionStartedByMe);

                UI32                         getNumberOfFailures                           () const;
                void                         setNumberOfFailures                           (const UI32 &numberOfFailures);
                void                         incrementNumberOfFailures                     ();
                void                         incrementNumberOfFailures                     (const UI32 &numberOfFailures);

                vector<WaveManagedObject *> *getPQueryResults                              () const;
                void                         setPQueryResults                              (vector<WaveManagedObject *> *pQueryResults);

        virtual void                         addManagedObjectsForGarbageCollection         (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection);
        virtual void                         addManagedObjectForGarbageCollection          (WaveManagedObject *pWaveManagedObjectForGarbageCollection);

                bool                         getIsADelayedCommitTransaction                () const;
                void                         setIsADelayedCommitTransaction                (const bool &isADelayedCommitTransaction);

    // Now the data members

    private :
        WaveMessage                *m_pWaveMessage;
        WaveAsynchronousContext    *m_pWaveAsynchronousContext;
        WaveElement                *m_pWaveElement;
        WaveLinearSequencerStep    *m_pSteps;
        UI32                         m_numberOfSteps;
        UI32                         m_currentStep;
        UI32                         m_numberOfCallbacksBeforeAdvancingToNextStep;
        ResourceId                   m_completionStatus;
        bool                         m_isHoldAllRequested;
        bool                         m_isTransactionStartedByMe;

        UI32                         m_numberOfFailures;

        vector<WaveManagedObject *> *m_pQueryResults;
        vector<WaveManagedObject *>  m_managedObjectsForGarbageCollection;

        struct timespec              m_ts1;
        struct timespec              m_ts2;
        struct timespec              m_tsr1;
        struct timespec              m_tsr2;
        SI32                         m_returnValue;
        SI32                         m_returnValueR;
        UI32                         m_operationCode;
    
        bool                         m_isADelayedCommitTransaction;

        clockid_t                    m_clockId;

    protected :
    public :
};

}

#endif //WAVELINEARSEQUENCERCONTEXT_H
