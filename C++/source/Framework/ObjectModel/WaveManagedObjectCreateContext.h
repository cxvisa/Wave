/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTCREATECONTEXT_H
#define WAVEMANAGEDOBJECTCREATECONTEXT_H

#include "ObjectId.h"
#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/WaveManagedObjectUpdateContext.h"

namespace WaveNs
{

class WaveManagedObject;

class WaveManagedObjectCreateContext : public WaveManagedObjectUpdateContext
{
    private :
    protected :
    public :
                                    WaveManagedObjectCreateContext           (WaveMessage* pWaveMessage, PrismElement* pPrismElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps);
                                    WaveManagedObjectCreateContext           (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement* pPrismElement, PrismLinearSequencerStep* pSteps, UI32 numberOfSteps);
        virtual                    ~WaveManagedObjectCreateContext           ();

                string              getManagedObjectClassNameNeedToBeCreated () const;
                void                setManagedObjectClassNameNeedToBeCreated (const string &managedObjectClassName);

                bool                isNeedToCreateManagedObject              () const;
                void                setNeedToCreateManagedObject             (const bool &needToCreateManagedObject);
                
                vector<Attribute*>  getChildAttributeVector                  () const;
                void                addToChildAttributeVector                (Attribute *pAttribute);
        // Now the data members

    private :
                string                                  m_managedObjectClassName;
                bool                                    m_needToCreateManagedObject;
                vector<Attribute *>                     m_childAttributes;

    protected :
    public :
};

}
#endif // WAVEMANAGEDOBJECTCREATECONTEXT_H

