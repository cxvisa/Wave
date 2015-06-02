/*************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                  *
 *   All rights reserved.                                    *
 *   Author : Jayaraman Iyer                                 *
 *************************************************************/

#ifndef FILESVCLOCALMESSAGINGTESTOBJECTMANAGER_H
#define FILESVCLOCALMESSAGINGTESTOBJECTMANAGER_H

#include "Regression/PrismTestObjectManager.h"
#include "File/Local/FilePushFileMessage.h"

namespace WaveNs
{
class CopyFileWaveClientMessage;
class CopyFileToHaPeerWaveClientMessage;

class FileLocalMessagingTestObjectManager : public PrismTestObjectManager
{
     private :
          FileLocalMessagingTestObjectManager ();
          WaveMessageStatus                                                          simpleSynchronousMessageTest            (PrismMessage *message);
          WaveMessageStatus                                                          simpleAsynchronousMessageTest           (PrismLinearSequencerContext *&pPrismLinearSequencerContext, vector<PrismMessage *>&sagesVector);
          void                                                                       CleanupTempFiles                        (void);
          void                                                                       SetupTempFileForTransfer                (UI32 nFileSize, const string &sFileName);
          void                                                                       ASynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTestCallback(FrameworkStatus frameworkStatus, FilePushFileMessage *pMessage, PrismLinearSequencerContext          
                                                                                                                                                           *pPrismLinearSequencerContext);
          void                                                                       ASyncPushFileWith1KDatatoGoodLocationIdTestCallback(FrameworkStatus frameworkStatus, FilePushFileMessage *pMessage, PrismLinearSequencerContext *pPrismLinearSequencerContext);
          
     protected :
     public :
          virtual                                                                   ~FileLocalMessagingTestObjectManager     ();
          static  PrismServiceId                                                     getPrismServiceId                       ();
          void                                                                       testRequestHandler                      (RegressionTestMessage *pMessage);
          static  FileLocalMessagingTestObjectManager                               *getInstance                             ();
          static  string                                                             getServiceName                          ();
                  PrismMessage                                                      *createMessageInstance                   (const UI32 &operationCode);


          void    simplePushFileWithInvalidFilenameTest                              (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          void    simplePushFileWithInvalidFilesizeTest                              (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          void    simplePushFileWithInvalidLocationIdTest                            (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          
          void    simpleSyncPushFileWith1KDatatoGoodLocationIdTest                   (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          void    simpleASyncPushFileWith1KDatatoGoodLocationIdTest                  (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          
          void    SynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTest        (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          void    ASynchronousDistributeFileWith1MBDatatoAllGoodLocationIdTest       (PrismLinearSequencerContext *pPrismLinearSequencerContext);
          void    CleanupTempTestFiles                                               (PrismLinearSequencerContext *pPrismLinearSequencerContext);

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
