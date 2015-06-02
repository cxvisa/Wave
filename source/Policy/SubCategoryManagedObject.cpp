/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/SubCategoryManagedObject.h"
#include "Policy/PolicyObjectManager.h"
#include "Framework/Attributes/Attributes.h"
#include "Policy/PfrThresholdTemplateManagedObject.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

SubCategoryManagedObject::SubCategoryManagedObject (PolicyObjectManager *pPolicyObjectManager)
    : PrismElement (pPolicyObjectManager),
      PrismPersistableObject (SubCategoryManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pPolicyObjectManager)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

SubCategoryManagedObject::~SubCategoryManagedObject ()
{
}

string SubCategoryManagedObject::getClassName ()
{
    return ("SubCategoryManagedObject");
}

void SubCategoryManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeObjectIdAssociation (&m_pfrThresholdTemplateObjectId, "pfrThresholdTemplateObjectId", PfrThresholdTemplateManagedObject::getClassName ()));
}

void SubCategoryManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeObjectIdAssociation (&m_pfrThresholdTemplateObjectId, "pfrThresholdTemplateObjectId", PfrThresholdTemplateManagedObject::getClassName ()));
}

void SubCategoryManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

ObjectId SubCategoryManagedObject::getPfrThresholdTemplateObjectId () const
{
    return (m_pfrThresholdTemplateObjectId);
}

void SubCategoryManagedObject::setPfrThresholdTemplateObjectId (const ObjectId &pfrThresholdTemplateObjectId)
{
    m_pfrThresholdTemplateObjectId = pfrThresholdTemplateObjectId;
}

}

