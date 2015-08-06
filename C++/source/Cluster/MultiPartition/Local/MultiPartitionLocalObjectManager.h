/*********************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                     *
 *   All rights reserved.                                            *
 *   Author : Jayaraman Iyer                                         *
 *********************************************************************/

#ifndef MULTIPARTITIONLOCALOBJECTMANAGER_H
#define MULTIPARTITIONLOCALOBJECTMANAGER_H

#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Cluster/MultiPartition/Global/MultiPartitionMessages.h"

using namespace WaveNs;

namespace WaveNs
{
    class MultiPartitionDeletePartitionMessage;

    class MultiPartitionLocalObjectManager: public WaveLocalObjectManager
    {
        private:
               MultiPartitionLocalObjectManager                                 ();
               PrismMessage      *createMessageInstance                       (const UI32 &operationCode);
               void               tenancyDeleteMessageHandler                 (MultiPartitionDeletePartitionMessage *pMultiPartitionDeletePartitionMessage);
                        
               // More private methods.
               ResourceId         validateInputs                              (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
               ResourceId         processPartitionObjectCleanup                 (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

        protected:
        public:
               virtual                                      ~MultiPartitionLocalObjectManager      ();
               static MultiPartitionLocalObjectManager        *getInstance                         ();
               static WaveServiceId                         getWaveServiceId                   ();
               static string                                 getServiceName                      ();

        // Now the data members
        private:

        protected:
        public:
    };

}
#endif    //  MULTIPARTITIONLOCALOBJECTMANAGER_H
