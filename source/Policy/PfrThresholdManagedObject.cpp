/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThresholdManagedObject.h"
#include "Policy/PolicyObjectManager.h"

namespace WaveNs
{

PfrThresholdManagedObject::PfrThresholdManagedObject (PolicyObjectManager *pPolicyObjectManager)
    : PrismElement                      (pPolicyObjectManager),
      PrismPersistableObject            (PfrThresholdManagedObject::getClassName (), PfrThresholdTemplateManagedObject::getClassName ()),
      PfrThresholdTemplateManagedObject (pPolicyObjectManager)
{
}

PfrThresholdManagedObject::~PfrThresholdManagedObject ()
{
}

string PfrThresholdManagedObject::getClassName ()
{
    return ("PfrThresholdManagedObject");
}

void PfrThresholdManagedObject::setupAttributesForPersistence ()
{
    PfrThresholdTemplateManagedObject::setupAttributesForPersistence ();
}

void PfrThresholdManagedObject::setupAttributesForCreate ()
{
}

}
