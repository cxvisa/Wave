/*********************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                     *
 *   All rights reserved.                                            *
 *   Author : jiyer                                                  *
 *********************************************************************/

#ifndef FILELOCALOBJECTMANAGER_H
#define FILELOCALOBJECTMANAGER_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "File/Local/FilePushFileMessage.h"
#include "File/Local/FileAbortFileTransferMessage.h"
#include "File/Local/FilePushFileFragmentMessage.h"
#include "File/Local/FileTransferHandshakeMessage.h"
#include "File/Local/FileTransferManagedObject.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Utils/PrismSynchronousLinearSequencerContext.h"

using namespace WaveNs;

namespace WaveNs
{
     class CFileFragment;
     class FilePushFileMessage;
     class FilePushFileFragmentMessage;
     class FileAbortFileTransferMessage;
     class FileTransferHandshakeMessage;
     class CFileTransferManagedObject; 
     class PushFileToHaPeerMessage;
     class FileDeleteRequestMessage;
     class FileDeleteFileMessage;
     class FileDeleteFileToHaPeerMessage; 

    class FileLocalObjectManager: public WaveLocalObjectManager
    {
        private:
               FileLocalObjectManager                                         ();
               WaveMessage      *createMessageInstance                       (const UI32 &operationCode);
               WaveManagedObject *createManagedObjectInstance                 (const string &managedClassName);
               void               AbortFileTransferMessageHandler             (FileAbortFileTransferMessage *pFileAbortFileTransferMessage);
               void               PushFileMessageHandler                      (FilePushFileMessage *pPushFileMessage);
               void               FileTransferHandshakeMessageHandler         (FileTransferHandshakeMessage *pFileTransferHandshakeMessage);
               void               PushFileFragmentMessageHandler              (FilePushFileFragmentMessage *pPushFileFragmentMessage);
            // ResourceId         StartFileTransferCallback                   (FrameworkStatus frameworkStatus, FilePushFileFragmentMessage *pMessage, PrismLinearSequencerContext *pPrismLinearSequencerContext);          
            // ResourceId         TriggerFileTransferHandshake                (PrismLinearSequencerContext *pPrismLinearSequencerContext);            
            // ResourceId         TriggerFileTransferHandshakeCallback        (FrameworkStatus frameworkStatus, FileTransferHandshakeMessage *pMessage, PrismLinearSequencerContext *pPrismLinearSequencerContext);
                        
               void               StartFileTransferCallback                   (WaveSendToClusterContext *pWaveSendToClusterContext);
               ResourceId         TriggerAsyncFileTransferHandshake           (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               void               TriggerFileTransferHandshakeCallback        (WaveSendToClusterContext *pWaveSendToClusterContext);

               // More private methods.
               ResourceId         ValidateInputs                              (PrismLinearSequencerContext *pPrismLinearSequencerContext);

               void               validateLocationIdAndVersion				  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               void               validateTransferFlag						  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               void               addToIncomingQueue						  (PrismLinearSequencerContext *pPrismLinearSequencerContext);

               ResourceId         StartAsyncFileTransfer                      (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               ResourceId         ProcessFileFragmentMessage                  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               ResourceId         ProcessAbortFileTransferMessage             (PrismLinearSequencerContext *pPrismLinearSequencerContext);

               ResourceId         sendFileToHaPeer                            (const string &fthandle, const string &sourceFileName, const string &destinationFileName, const UI32 &fileSize);

               void               PushFileToHaPeerMessageHandler              (PushFileToHaPeerMessage *pPushFileToHaPeerMessage);
               ResourceId         pushFileToHaPeerValidateReceiptStep         (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
               ResourceId         pushFileToHaPeerReceiveFileStep             (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
               void               FilePushFileToHaPeerMessageHandler          (FilePushFileToHaPeerMessage *pFilePushFileToHaPeerMessage);
               ResourceId         pushFileToHaPeerValidateStep                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);
               ResourceId         pushFileToHaPeerSendFileStep                (PrismSynchronousLinearSequencerContext *pPrismSynchronousLinearSequencerContext);

               void               FileDeleteRequestFromServiceHandler         (FileDeleteRequestMessage *pFileDeleteRequestMessage);
               void               DeleteValidateStep                          ( PrismLinearSequencerContext *pPrismLinearSequencerContext ); 
               void               DeleteRequestFileTransferHandshake          (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               void               DeleteRequestFileTransferHandshakeCallback  (WaveSendToClusterContext *pWaveSendToClusterContext);    
               void               sendDeleteMessageToAll                      (PrismLinearSequencerContext *pPrismLinearSequencerContext);  
               void               sendDeleteMessageToAllCallback              (WaveSendToClusterContext *pWaveSendToClusterContext); 

               void               DeleteFileMessageHandler                    (FileDeleteFileMessage *pFileDeleteFileMessage);
               void               DeleteFileStep                              (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               ResourceId         sendDeleteFileToHAPeer                      ( const string &filename, const UI32 &transferFlag );   

               void               DeleteFileOnHaPeerMessageHandler            (FileDeleteFileToHaPeerMessage *pFileDeleteFileToHaPeerMessage);
               void               DeleteFileHaPeerStep                        (PrismLinearSequencerContext *pPrismLinearSequencerContext);
               SI32               DeleteFile                                  (const string &filename);        

        protected:
        public:
               virtual                               ~FileLocalObjectManager                      ();
               static FileLocalObjectManager         *getInstance                                 ();
               static string                          getClassName                                ();
               static WaveServiceId                  getWaveServiceId                           ();
               UI32                                   getFileServiceVersion                       () const;

        // Now the data members
        private:
               UI32                                  m_nFileServiceVersion;                  // For future compatibility.
               class  CFileTransferManagedObject     m_FTTable;                              // File transfer table.

        protected:
        public:
    };

}
#endif    //  FILELOCALOBJECTMANAGER_H
