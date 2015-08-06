/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka, Himanshu Varshney                 *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTUPDATEWORKER_H
#define WAVEMANAGEDOBJECTUPDATEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"

namespace WaveNs
{

class WaveObjectManagerUpdateWaveManagedObjectMessage;
class WaveManagedObjectUpdateContext;
class UnifiedClientUpdateMessage;
class WaveObjectManagerUpdateRelationshipMessage;
class WaveManagedObjectAsynchronousCreateContext;

class WaveManagedObjectUpdateWorker : public WaveWorker
{
    private :
        WaveMessage *createMessageInstance         (const UI32 &operationCode);

        void        updateHandler                                   (WaveObjectManagerUpdateWaveManagedObjectMessage *pWaveObjectManagerUpdateWaveManagedObjectMessage);
        void        updateQueryManagedObjectStep                    (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateValidateManagedObjectStep                 (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        validateForUpdateAtThisNodeCallBack             (ValidateForUpdateAtThisNodeContext *pValidateForUpdateAtThisNodeContext);
        void        updatePreUpdateManagedObjectStep                (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateUpdateManagedObjectStep                   (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updatePostUpdateManagedObjectStep               (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updatePreUpdateHardwareStep                     (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updatePreUpdateHardwareStepCallback             (PrismAsynchronousContext *pPrismAsynchronousContext);
        void        updateUpdateHardwareStep                        (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateUpdateHardwareStepCallBack                (GetHardwareConfigurationDetailsForUpdateContext *pGetHardwareConfigurationDetailsForUpdateContext);
        void        updatePostUpdateHardwareStep                     (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateRelationshipMessageHandler                (WaveObjectManagerUpdateRelationshipMessage  *pWaveObjectManagerUpdateRelationshipMessage);
        void        isAssociatedManagedObjectToBeCreatedCallback    (IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext);
        ObjectId    createAssociatedManagedObject                   (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext, IsAssociatedManagedObjectToBeCreatedContext *pAssociatedContext, string associatedClassName, string associatedAttributeName, string associatedAttributeValue);
        void        commitWaveManagedObjectBeforeUpdatingBackend    (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        commitWaveManagedObjectAfterUpdatingBackend     (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateUpdateNewAttributeInManagedObject         (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateUpdateNewAttributeInManagedObjectCallback (UpdateNewAttributeInManagedObjectContext *pUpdateNewAttributeInManagedObjectContext);
        void        populateManagedObjectKeyAttributes              (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        populateParentKeyAttributes                     (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        string      getClientNameToSendAndPopulateRelatedAttributes (GetHardwareConfigurationDetailsForUpdateContext *pGetHardwareConfigurationDetailsForUpdateContext);
        void        createAssociatedManagedObjectCallback           (WaveManagedObjectAsynchronousCreateContext *pWaveManagedObjectAsynchronousCreateContext);
        void        WaveManagedObjectStartTransactionStep           (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);
        void        updateAttributesPostUpdateHardwareStep          (WaveManagedObjectUpdateContext *pWaveManagedObjectUpdateContext);

    protected :
    public :
                 WaveManagedObjectUpdateWorker      (WaveObjectManager *pWaveObjectManger);
        virtual ~WaveManagedObjectUpdateWorker      ();

    // Now the data members

    private :
    protected :
    public :
};

}
#endif // WAVEMANAGEDOBJECTUPDATEWORKER_H

