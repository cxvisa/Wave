/*********************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                     *
 *   All rights reserved.                                            *
 *   Author : jiyer                                                  *
 *********************************************************************/

#ifndef FILELOCALOBJECTMANAGER_H
#define FILELOCALOBJECTMANAGER_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "File/Local/FilePushFileMessage.h"
#include "File/Local/FileAbortFileTransferMessage.h"
#include "File/Local/FilePushFileFragmentMessage.h"
#include "File/Local/FileTransferHandshakeMessage.h"
#include "File/Local/FileTransferManagedObject.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"
#include "Framework/Utils/WaveSynchronousLinearSequencerContext.h"

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
            // ResourceId         StartFileTransferCallback                   (FrameworkStatus frameworkStatus, FilePushFileFragmentMessage *pMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);          
            // ResourceId         TriggerFileTransferHandshake                (WaveLinearSequencerContext *pWaveLinearSequencerContext);            
            // ResourceId         TriggerFileTransferHandshakeCallback        (FrameworkStatus frameworkStatus, FileTransferHandshakeMessage *pMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
                        
               void               StartFileTransferCallback                   (WaveSendToClusterContext *pWaveSendToClusterContext);
               ResourceId         TriggerAsyncFileTransferHandshake           (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               void               TriggerFileTransferHandshakeCallback        (WaveSendToClusterContext *pWaveSendToClusterContext);

               // More private methods.
               ResourceId         ValidateInputs                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);

               void               validateLocationIdAndVersion				  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               void               validateTransferFlag						  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               void               addToIncomingQueue						  (WaveLinearSequencerContext *pWaveLinearSequencerContext);

               ResourceId         StartAsyncFileTransfer                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               ResourceId         ProcessFileFragmentMessage                  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               ResourceId         ProcessAbortFileTransferMessage             (WaveLinearSequencerContext *pWaveLinearSequencerContext);

               ResourceId         sendFileToHaPeer                            (const string &fthandle, const string &sourceFileName, const string &destinationFileName, const UI32 &fileSize);

               void               PushFileToHaPeerMessageHandler              (PushFileToHaPeerMessage *pPushFileToHaPeerMessage);
               ResourceId         pushFileToHaPeerValidateReceiptStep         (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
               ResourceId         pushFileToHaPeerReceiveFileStep             (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
               void               FilePushFileToHaPeerMessageHandler          (FilePushFileToHaPeerMessage *pFilePushFileToHaPeerMessage);
               ResourceId         pushFileToHaPeerValidateStep                (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);
               ResourceId         pushFileToHaPeerSendFileStep                (WaveSynchronousLinearSequencerContext *pWaveSynchronousLinearSequencerContext);

               void               FileDeleteRequestFromServiceHandler         (FileDeleteRequestMessage *pFileDeleteRequestMessage);
               void               DeleteValidateStep                          ( WaveLinearSequencerContext *pWaveLinearSequencerContext ); 
               void               DeleteRequestFileTransferHandshake          (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               void               DeleteRequestFileTransferHandshakeCallback  (WaveSendToClusterContext *pWaveSendToClusterContext);    
               void               sendDeleteMessageToAll                      (WaveLinearSequencerContext *pWaveLinearSequencerContext);  
               void               sendDeleteMessageToAllCallback              (WaveSendToClusterContext *pWaveSendToClusterContext); 

               void               DeleteFileMessageHandler                    (FileDeleteFileMessage *pFileDeleteFileMessage);
               void               DeleteFileStep                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
               ResourceId         sendDeleteFileToHAPeer                      ( const string &filename, const UI32 &transferFlag );   

               void               DeleteFileOnHaPeerMessageHandler            (FileDeleteFileToHaPeerMessage *pFileDeleteFileToHaPeerMessage);
               void               DeleteFileHaPeerStep                        (WaveLinearSequencerContext *pWaveLinearSequencerContext);
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
