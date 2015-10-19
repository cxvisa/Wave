/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTCREATEWORKER_H
#define WAVEMANAGEDOBJECTCREATEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"

namespace WaveNs
{

class WaveObjectManagerCreateWaveManagedObjectMessage;
class WaveManagedObjectCreateContext;
class UnifiedClientCreateMessage;
class WaveManagedObjectAsynchronousCreateContext;

class WaveManagedObjectCreateWorker : public WaveWorker
{
    private :
        WaveMessage       *createMessageInstance                           (const UI32 &operationCode);

        void                createHandler                                   (WaveObjectManagerCreateWaveManagedObjectMessage *pWaveObjectManagerCreateWaveManagedObjectMessage);
        void                createQueryManagedObjectStep                    (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createValidateManagedObjectStep                 (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                validateForCreateAtThisNodeCallBack             (ValidateForCreateAtThisNodeContext *pValidateForCreateAtThisNodeContext);
        void                createPreUpdateManagedObjectStep                (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createUpdateManagedObjectStep                   (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createPostUpdateManagedObjectStep               (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createPostUpdateManagedObjectCallBack           (WaveAsynchronousContext *pWaveAsynchronousContext);
        void                createPreUpdateHardwareStep                     (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createPreUpdateHardwareStepCallback             (WaveAsynchronousContext *pWaveAsynchronousContext);
        void                createUpdateHardwareStep                        (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createUpdateHardwareStepCallBack                (GetHardwareConfigurationDetailsForCreateContext *pGetHardwareConfigurationDetailsForCreateContext);
        void                createPostUpdateHardwareStep                    (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        WaveManagedObject  *createManagedObject                             (const string &className);
        ResourceId          updateRelationship                              (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext, const string &parentClassName, const string &childClassName, const string &relationshipName, const ObjectId &parentObjectId, const ObjectId &childObjectId);

        void                isAssociatedManagedObjectToBeCreatedCallback    (IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext);
        ObjectId            createAssociatedManagedObject                   (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext, IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext, string associatedClassName, string associatedAttributeName, string associatedAttributeValue);
        void                commitWaveManagedObjectBeforeUpdatingBackend    (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                commitWaveManagedObjectAfterUpdatingBackend     (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createUpdateNewAttributeInManagedObject         (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createUpdateNewAttributeInManagedObjectCallback (UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext);
        void                populateParentKeyAttributes                     (GetHardwareConfigurationDetailsForCreateContext *pGetHardwareConfigurationDetailsForCreateContext);
        void                populateKeyAttributesIfNotPresent               (GetHardwareConfigurationDetailsForCreateContext *pGetHardwareConfigurationDetailsForCreateContext);
        string              getClientNameToSendAndPopulateRelatedAttributes (GetHardwareConfigurationDetailsForCreateContext *pGetHardwareConfigurationDetailsForCreateContext);
        void                asynchronousCreateHandler                       (WaveManagedObjectAsynchronousCreateContext *pWaveManagedObjectAsynchronousCreateContext);
        void                createUpdateHardwareStepForChildCallBack        (GetHardwareConfigurationDetailsForCreateContext *pGetHardwareConfigurationDetailsForCreateContext);
        void                createUpdateHardwareStepForChild                (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                WaveManagedObjectStartTransactionStep           (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);
        void                createAttributesPostUpdateHardwareStep          (WaveManagedObjectCreateContext *pWaveManagedObjectCreateContext);

    protected :
    public :
                            WaveManagedObjectCreateWorker           (WaveObjectManager *pWaveObjectManger);
        virtual            ~WaveManagedObjectCreateWorker           ();

    // Now the data members

    private :
    protected :
    public :
       friend class WaveManagedObjectUpdateWorker;
};

}
#endif // WAVEMANAGEDOBJECTCREATEWORKER_H

