/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayaraman Iyer                                               *
 ***************************************************************************/

#ifndef MULTIPARTITIONOBJECTMANAGER_H
#define MULTIPARTITIONOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Cluster/MultiPartition/Global/MultiPartitionMessages.h"
#include "Cluster/MultiPartition/Global/MultiPartitionSequencerContext.h"

namespace WaveNs
{

class MultiPartitionObjectManager : public WaveObjectManager
{
    private :
                // sequencer methods.
                
                // ADD
                ResourceId                     validateInputsForAddPartition                    (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);
                ResourceId                     createPartitionManagedObjectStep                 (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);

                // DELETE
                ResourceId                     validateInputsForDeletePartition                 (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);
                ResourceId                     deletePartitionManagedObject                     (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);
                ResourceId                     triggerPartitionCleanupForLocalServicesStep      (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);
                ResourceId                     triggerPartitionCleanupForGlocalServicesStep     (MultiPartitionSynchronousLinearSequencerContext *pMultiPartitionSynchronousLinearSequencerContext);
                void                            getObjectIdForPartitionNameMessageHandler       (MultiPartitionObjectManagerGetObjectIdForPartitionNameMessage *pMultiPartitionObjectManagerGetObjectIdForPartitionNameMessage);

    protected :
    public :
                                                MultiPartitionObjectManager                     ();
        virtual                                ~MultiPartitionObjectManager                     ();

        virtual PrismMessage                   *createMessageInstance                           (const UI32 &operationCode);
                WaveManagedObject              *createManagedObjectInstance                     (const string &managedClassName);
                void                            initialize                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                            install                                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
                void                            boot                                            (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
//              void                            shutdown                                        (WaveAsynchronousContextForShutdownPhases *pWaveAsynchronousContextForShutdownPhases);
                void                            haboot                                          (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void                            failover                                        (FailoverAsynchronousContext *pFailoverAsynchronousContext);


        static  string                          getServiceName                                  ();
        static  MultiPartitionObjectManager    *getInstance                                     ();
        static  WaveServiceId                  getWaveServiceId                               ();

        // Message Handlers.
                void                            addPartitionMessageHandler                      (MultiPartitionAddPartitionMessage *pMultiPartitionAddPartitionMessage); 
                void                            deletePartitionMessageHandler                   (MultiPartitionDeletePartitionMessage *pMultiPartitionDeletePartitionMessage); 
                ObjectId                        getObjectIdForPartitionName                     (const string &partitionName);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // MULTIPARTITIONOBJECTMANAGER_H
