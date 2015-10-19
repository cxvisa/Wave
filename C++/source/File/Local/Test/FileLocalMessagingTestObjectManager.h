/*************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                  *
 *   All rights reserved.                                    *
 *   Author : Jayaraman Iyer                                 *
 *************************************************************/

#ifndef FILESVCLOCALMESSAGINGTESTOBJECTMANAGER_H
#define FILESVCLOCALMESSAGINGTESTOBJECTMANAGER_H

#include "Regression/WaveTestObjectManager.h"
#include "File/Local/FilePushFileMessage.h"

namespace WaveNs
{
class CopyFileWaveClientMessage;
class CopyFileToHaPeerWaveClientMessage;

class FileLocalMessagingTestObjectManager : public WaveTestObjectManager
{
     private :
          FileLocalMessagingTestObjectManager ();
          WaveMessageStatus                                                          simpleSynchronousMessageTest            (WaveMessage *message);
          WaveMessageStatus                                                          simpleAsynchronousMessageTest           (WaveLinearSequencerContext *&pWaveLinearSequencerContext, vector<WaveMessage *>&sagesVector);
          void                                                                       CleanupTempFiles                        (void);
          void                                                                       SetupTempFileForTransfer                (UI32 nFileSize, const string &sFileName);
          void                                                                       ASynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTestCallback(FrameworkStatus frameworkStatus, FilePushFileMessage *pMessage, WaveLinearSequencerContext          
                                                                                                                                                           *pWaveLinearSequencerContext);
          void                                                                       ASyncPushFileWith1KDatatoGoodLocationIdTestCallback(FrameworkStatus frameworkStatus, FilePushFileMessage *pMessage, WaveLinearSequencerContext *pWaveLinearSequencerContext);
          
     protected :
     public :
          virtual                                                                   ~FileLocalMessagingTestObjectManager     ();
          static  WaveServiceId                                                     getWaveServiceId                       ();
          void                                                                       testRequestHandler                      (RegressionTestMessage *pMessage);
          static  FileLocalMessagingTestObjectManager                               *getInstance                             ();
          static  string                                                             getServiceName                          ();
                  WaveMessage                                                      *createMessageInstance                   (const UI32 &operationCode);


          void    simplePushFileWithInvalidFilenameTest                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          void    simplePushFileWithInvalidFilesizeTest                              (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          void    simplePushFileWithInvalidLocationIdTest                            (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          
          void    simpleSyncPushFileWith1KDatatoGoodLocationIdTest                   (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          void    simpleASyncPushFileWith1KDatatoGoodLocationIdTest                  (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          
          void    SynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTest        (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          void    ASynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTest       (WaveLinearSequencerContext *pWaveLinearSequencerContext);
          void    CleanupTempTestFiles                                               (WaveLinearSequencerContext *pWaveLinearSequencerContext);

          void    copyFileWaveClientMessageHandler                                   (CopyFileWaveClientMessage *pCopyFileWaveClientMessage);
          void    copyFileToHaPeerWaveClientMessageHandler                           (CopyFileToHaPeerWaveClientMessage *pCopyFileToHaPeerWaveClientMessage);

     // Now the data members
     private :
          static FileLocalMessagingTestObjectManager                             *m_pVcsNodeLocalMessagingTestObjectManager;

          

     protected :
     public:
};

}

#endif // FILESVCLOCALMESSAGINGTESTOBJECTMANAGER_H
