/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#ifndef FILEOBJECTMANAGER_H
#define FILEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WaveManagedObjectSynchronousQueryContext.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"


using namespace WaveNs;

namespace WaveNs
{

    class FILESVCAbortFileTransferMessage;

    class FileObjectManager: public WaveObjectManager
    {
        private:
            PrismMessage      *createMessageInstance                       (const UI32 &operationCode);
            WaveManagedObject *createManagedObjectInstance                 (const string &managedClassName);
            void              FILESVCAbortFileTransferMessageHandler       (FILESVCAbortFileTransferMessage *pFILESVCAbortFileTransferMessage);
            void              boot                                         (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
            void              install                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
		  void              disable                                      (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
		  void              shutdown                                     (PrismAsynchronousContext *pPrismAsynchronousContext);
  		  void              failover                                     (FailoverAsynchronousContext *pFailoverAsynchronousContext);
		  void              listenForEvents                              (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
            void              TriggerFailOverCallback                      (WaveSendToClusterContext *pWaveSendToClusterContext );
                        
        protected:
        public:
                                             FileObjectManager             ();
            virtual                         ~FileObjectManager             ();
            static FileObjectManager        *getInstance                   ();
            static string                    getClassName                  ();
            static PrismServiceId            getPrismServiceId             ();

        // Now the data members
        private:

        protected:
        public:
    };
}
#endif    //FILEOBJECTMANAGER_H
