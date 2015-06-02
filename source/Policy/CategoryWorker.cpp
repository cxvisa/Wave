/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/CategoryWorker.h"
#include "Policy/PolicyObjectManager.h"
#include "Policy/PolicyObjectManagerTypes.h"
#include "Policy/CategoryManagedObject.h"
#include "Policy/PfrThresholdManagedObject.h"
#include "Policy/PfrThresholdTemplateManagedObject.h"
#include "Policy/SubCategoryManagedObject.h"

namespace WaveNs
{

CategoryWorker::CategoryWorker (PolicyObjectManager *pPolicyObjectManager)
    : WaveWorker (pPolicyObjectManager)
{
    CategoryManagedObject             categoryManagedObject             (pPolicyObjectManager);
    PfrThresholdTemplateManagedObject pfrThresholdTemplateManagedObject (pPolicyObjectManager);
    SubCategoryManagedObject          subCategoryManagedObject          (pPolicyObjectManager);
    PfrThresholdManagedObject         pfrThresholdManagedObject         (pPolicyObjectManager);

    categoryManagedObject.setupOrm ();
    addManagedClass (CategoryManagedObject::getClassName (), this);

    pfrThresholdTemplateManagedObject.setupOrm ();
    addManagedClass (PfrThresholdTemplateManagedObject::getClassName (), this);

    subCategoryManagedObject.setupOrm ();
    addManagedClass (SubCategoryManagedObject::getClassName (), this);

    pfrThresholdManagedObject.setupOrm ();
    addManagedClass (PfrThresholdManagedObject::getClassName (), this);
}

CategoryWorker::~CategoryWorker ()
{
}

WaveManagedObject *CategoryWorker::createManagedObjectInstance (const string &className)
{
    WaveManagedObject   *pWaveManagedObject   = NULL;
    PolicyObjectManager *pPolicyObjectManager = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

    prismAssert (NULL != pPolicyObjectManager, __FILE__, __LINE__);

    return (pWaveManagedObject);
}

}

