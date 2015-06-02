/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/CategoryManagedObject.h"
#include "Policy/PolicyObjectManager.h"
#include "Framework/Attributes/Attributes.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

CategoryManagedObject::CategoryManagedObject (PolicyObjectManager *pPolicyObjectManager)
    : PrismElement (pPolicyObjectManager),
      PrismPersistableObject (CategoryManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pPolicyObjectManager)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

CategoryManagedObject::~CategoryManagedObject ()
{
}

string CategoryManagedObject::getClassName ()
{
    return ("CategoryManagedObject");
}

void CategoryManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();
}

void CategoryManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();
}

void CategoryManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

}

