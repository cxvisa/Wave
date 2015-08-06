/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTUPDATECONTEXT_H
#define WAVEMANAGEDOBJECTUPDATECONTEXT_H

#include "ObjectId.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"

namespace WaveNs
{

class WaveManagedObject;
class WaveManagedObjectCreateContext;
class Attribute;

class WaveManagedObjectUpdateContext : public PrismLinearSequencerContext
{
    private :
    protected :
    public :
                                           WaveManagedObjectUpdateContext               (WaveMessage* pWaveMessage, WaveElement* pWaveElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps);
                                           WaveManagedObjectUpdateContext               (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement* pWaveElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps);
        virtual                           ~WaveManagedObjectUpdateContext               ();

                ObjectId                   getInputWaveManagedObjectId                  () const;
                void                       setInputWaveManagedObjectId                  (const ObjectId &waveManagedObjectId);

                ObjectId                   getOperateOnWaveManagedObjectId              () const;
                void                       setOperateOnWaveManagedObjectId              (const ObjectId &waveManagedObjectId);

                WaveManagedObject * const  getPInputWaveManagedObject                   () const;
                void                       setPInputWaveManagedObject                   (WaveManagedObject * const pWaveManagedObject);

                WaveManagedObject * const  getPOperateOnWaveManagedObject               () const;
                void                       setPOperateOnWaveManagedObject               (WaveManagedObject * const pWaveManagedObject);

                vector<UI32>               getAttributeUserTags                         () const;
                void                       setAttributeUserTags                         (const vector<UI32> &attributeUserTags);

                vector<string>             getAttributeNames                            () const;
                void                       setAttributeNames                            (const vector<string> &attributeNames);

                vector<string>             getAttributeValues                           () const;
                void                       setAttributeValues                           (const vector<string> &attributeValues);

                vector<Attribute* >        getAttributes                                () const;
                void                       addToAttributeVector                         (Attribute *pAttribute);

                ObjectId                   getParentObjectId                            () const;
                void                       setParentObjectId                            (const ObjectId &parentObjectId);

                UI32                       getChildUserTag                              () const;
                void                       setChildUserTag                              (const UI32 &childUserTag);
                
                ResourceId                 getErrorInCreatingMO                         () const;
                void                       setErrorInCreatingMO                         (const ResourceId &errorInCreatingMO);

                void                       addAysnchronousContextForGarbageCollection   (PrismAsynchronousContext *prismAsynchronousContext);

        virtual void                       addManagedObjectForGarbageCollection         (WaveManagedObject *pWaveManagedObjectForGarbageCollection);
               
                void                       setIsDatabaseUpdateRequired                  (bool isDatabaseUpdateRequired);
                bool                       getIsDatabaseUpdateRequired                  ();
                
                void                       setIsBackendUpdateRequired                   (bool isBackendUpdateRequired);
                bool                       getIsBackendUpdateRequired                   ();      
                
                 void                      setParentManagedObjectNames                  (vector<string> parentManagedObjectNames);
                 vector<string>            getParentManagedObjectNames                  ();
                 
                 void                      setMessage                                   (WaveMessage *pMessage);
                 WaveMessage*             getMessage                                   ();

                 void                      setAssociatedFromManagedObjectName           (string associatedFromMOName);
                 string                    getAssociatedFromManagedObjectName           (); 

                 UI32                      getChoiceUserTagNeedToRemove                 () const;
                 void                      setChoiceUserTagNeedToRemove                 (const UI32 &choiceUserTagNeedToRemove);

                 bool                      getConfigReplayInProgressFlag                () const;
                 void                      setConfigReplayInProgressFlag                (const bool isConfigReplayInProgress);

                 vector<string>             getAttributeNamesFromBackend                () const;
                 void                       setAttributeNamesFromBackend                (const vector<string> &attributeNamesFromBackend);
 
                 vector<string>             getAttributeValuesFromBackend               () const;
                 void                       setAttributeValuesFromBackend               (const vector<string> &attributeValuesFromBackend);
                                
        // Now the data members

    private :
        ObjectId                                m_inputWaveManagedObjectId;
        ObjectId                                m_operateOnWaveManagedObjectId;
        WaveManagedObject                      *m_pInputWaveManagedObject;
        WaveManagedObject                      *m_pOperateOnWaveManagedObject;
        vector<UI32>                            m_attributeUserTags;
        vector<string>                          m_attributeNames;
        vector<string>                          m_attributeValues;
        vector<Attribute *>                     m_attributes;
        ObjectId                                m_parentObjectId;
        UI32                                    m_childUserTag;
        ResourceId                              m_errorInCreatingMO;
        vector<PrismAsynchronousContext *>      m_prismAsynchronousContext;
        bool                                    m_isDatabaseUpdateRequired;
        bool                                    m_isBackendUpdateRequired;    
        vector<string>                          m_parentManagedObjectNames;
        WaveMessage                           *m_pMessage;
        string                                  m_associatedFromMOName;
        UI32                                    m_choiceUserTagNeedToRemove;
        bool                                    m_isConfigReplayInProgress;
        vector<string>                          m_attributeNamesFromBackend;
        vector<string>                          m_attributeValuesFromBackend;

    protected :
    public :
        friend class       WaveManagedObjectCreateContext;
        friend class       WaveManagedObjectDeleteContext;
};

}
#endif // WAVEMANAGEDOBJECTUPDATECONTEXT_H

