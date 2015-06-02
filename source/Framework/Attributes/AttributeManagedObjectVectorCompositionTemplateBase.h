/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ATTRIBUTEMANAGEDOBJECTVECTORCOMPOSITIONTEMPLATEBASE_H
#define ATTRIBUTEMANAGEDOBJECTVECTORCOMPOSITIONTEMPLATEBASE_H

#include "Framework/Attributes/Attribute.h"
#if 0
#include "Framework/ObjectModel/WaveManagedObjectPointer.cpp"
#include "WaveResourceIdEnums.h"
#endif

namespace WaveNs
{

class AttributeManagedObjectVectorCompositionTemplateBase : public Attribute
{
    private :
    protected :
                                                                       AttributeManagedObjectVectorCompositionTemplateBase  (AttributeType &attributeType, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational);
                                                                       AttributeManagedObjectVectorCompositionTemplateBase  (const AttributeManagedObjectVectorCompositionTemplateBase &attribute);
                AttributeManagedObjectVectorCompositionTemplateBase   &operator =                                           (const AttributeManagedObjectVectorCompositionTemplateBase &attribute);

    public :
        virtual void                                                   setDisableValidations                                (const bool disableValidations);
        virtual bool                                                   getDisableValidations                                () const;
        virtual void                                                   getCValue                                            (WaveCValue *pCValue);

        virtual void                                                   storeRelatedObjectVector                             (const ObjectId &parentObjectId, const vector<WaveManagedObject *> &vectorOfRelatedObjects);

    // Now the data members

    private :
        bool          m_disableValidations;
};

}

#endif // ATTRIBUTEMANAGEDOBJECTVECTORCOMPOSITIONTEMPLATEBASE_H

