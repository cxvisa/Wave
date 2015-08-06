/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTDELETEWORKER_H
#define WAVEMANAGEDOBJECTDELETEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"


namespace WaveNs
{

class WaveObjectManagerDeleteWaveManagedObjectMessage;
class WaveObjectManagerDeleteWaveManagedObjectsMessage;
class WaveManagedObjectDeleteContext;
class UnifiedClientDeleteMessage;

class WaveManagedObjectDeleteWorker : public WaveWorker
{
    private :
        WaveMessage   *createMessageInstance         (const UI32 &operationCode);

        void            deleteHandlerForMultipleDelete                      (WaveObjectManagerDeleteWaveManagedObjectsMessage *pWaveObjectManagerDeleteWaveManagedObjectsMessage);
        void            sendAsynchronousDeleteMessagesStep              (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteHandlerForMultipleDeleteCallback              (FrameworkStatus frameworkStatus, WaveMessage *pWaveMessage, void* pCallerContext);
        void            deleteHandler                                   (WaveObjectManagerDeleteWaveManagedObjectMessage *pWaveObjectManagerDeleteWaveManagedObjectMessage);
        void            deleteQueryManagedObjectStep                    (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteValidateManagedObjectStep                 (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            validateForDeleteAtThisNodeCallBack             (ValidateForDeleteAtThisNodeContext *pValidateForDeleteAtThisNodeContext);
        void            deletePreDeleteManagedObjectStep                (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteDeleteManagedObjectStep                   (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deletePostDeleteManagedObjectStep               (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deletePreUpdateHardwareStep                     (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deletePreUpdateHardwareStepCallback             (PrismAsynchronousContext *pPrismAsynchronousContext);
        void            deleteUpdateHardwareStep                        (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteUpdateHardwareStepCallBack                (GetHardwareConfigurationDetailsForDeleteContext *pGetHardwareConfigurationDetailsForDeleteContext);
        void            deletePostUpdateHardwareStep                    (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        ResourceId      updateRelationship                              (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext, const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);
        void            commitWaveManagedObjectBeforeUpdatingBackend    (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            commitWaveManagedObjectAfterUpdatingBackend     (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteUpdateNewAttributeInManagedObject         (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteUpdateNewAttributeInManagedObjectCallback (UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext);
        void            populateManagedObjectKeyAttributes              (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            populateParentKeyAttributes                     (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        string          getClientNameToSendAndPopulateRelatedAttributes (GetHardwareConfigurationDetailsForDeleteContext *pGetHardwareConfigurationDetailsForDeleteContext);
        
        ResourceId      deleteAssociations                              (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        void            deleteAssociationCallback                       (WaveSendToClusterContext *pWaveSendToClusterContext);
        void            WaveManagedObjectStartTransactionStep           (WaveManagedObjectDeleteContext *pWaveManagedObjectDeleteContext);
        
    protected :
    public :
                 WaveManagedObjectDeleteWorker      (WaveObjectManager *pWaveObjectManger);
        virtual ~WaveManagedObjectDeleteWorker      ();

    // Now the data members

    private :
    protected :
    public :
};

}
#endif // WAVEMANAGEDOBJECTDELETEWORKER_H

