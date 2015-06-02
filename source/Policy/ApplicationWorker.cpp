/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/ApplicationWorker.h"
#include "Policy/PolicyObjectManager.h"
#include "Policy/PolicyObjectManagerTypes.h"
#include "Policy/ApplicationManagedObject.h"

namespace WaveNs
{

ApplicationWorker::ApplicationWorker (PolicyObjectManager *pPolicyObjectManager)
    : WaveWorker (pPolicyObjectManager)
{
    ApplicationManagedObject applicationManagedObject (pPolicyObjectManager);

    applicationManagedObject.setupOrm ();
    addManagedClass (ApplicationManagedObject::getClassName (), this);
}

ApplicationWorker::~ApplicationWorker ()
{
}

WaveManagedObject *ApplicationWorker::createManagedObjectInstance (const string &className)
{
    WaveManagedObject   *pWaveManagedObject   = NULL;
    PolicyObjectManager *pPolicyObjectManager = dynamic_cast<PolicyObjectManager *> (getPWaveObjectManager ());

    prismAssert (NULL != pPolicyObjectManager, __FILE__, __LINE__);

    if (ApplicationManagedObject::getClassName () == className)
    {
        pWaveManagedObject = new ApplicationManagedObject (pPolicyObjectManager);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    return (pWaveManagedObject);
}

}

