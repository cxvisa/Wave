/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Attributes/AttributeManagedObjectVectorCompositionTemplateBase.h"
#include "Framework/Utils/AssertUtils.h"
#include <vector>

using namespace std;

namespace WaveNs
{
AttributeManagedObjectVectorCompositionTemplateBase::AttributeManagedObjectVectorCompositionTemplateBase (AttributeType &attributeType, const string &attributeName, const UI32 &attributeUserTag, const bool &isOperational)
    : Attribute             (AttributeType::AttributeTypeCompositionVector, attributeName, attributeUserTag, isOperational),
      m_disableValidations  (false)
{
}

AttributeManagedObjectVectorCompositionTemplateBase::AttributeManagedObjectVectorCompositionTemplateBase (const AttributeManagedObjectVectorCompositionTemplateBase &attributeManagedObjectVectorCompositionTemplateBase)
    : Attribute         (attributeManagedObjectVectorCompositionTemplateBase)
{
    m_disableValidations = attributeManagedObjectVectorCompositionTemplateBase.m_disableValidations;
}

AttributeManagedObjectVectorCompositionTemplateBase &AttributeManagedObjectVectorCompositionTemplateBase::operator = (const AttributeManagedObjectVectorCompositionTemplateBase &attributeManagedObjectVectorCompositionTemplateBase)
{
    Attribute::operator = (attributeManagedObjectVectorCompositionTemplateBase);

    m_disableValidations = attributeManagedObjectVectorCompositionTemplateBase.m_disableValidations;

    return (*this);
}

bool AttributeManagedObjectVectorCompositionTemplateBase::getDisableValidations () const
{
    return m_disableValidations;
}

void AttributeManagedObjectVectorCompositionTemplateBase::setDisableValidations (const bool disableValidations)
{
    m_disableValidations = disableValidations;
}

void AttributeManagedObjectVectorCompositionTemplateBase::getCValue (WaveCValue *pCValue)
{
    prismAssert (false, __FILE__, __LINE__); 
}

void AttributeManagedObjectVectorCompositionTemplateBase::storeRelatedObjectVector (const ObjectId &parentObjectId, const vector<WaveManagedObject *> &vectorOfRelatedObjects)
{
    prismAssert (false, __FILE__, __LINE__);
}

}
