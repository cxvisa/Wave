/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 ***************************************************************************/

#include "LockManagement/LockManagementMessagingContext.h"

namespace WaveNs
{

LockManagementMessagingContext::LockManagementMessagingContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismSynchronousLinearSequencerStep *pSteps, UI32 numberOfSteps) 
    : PrismSynchronousLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps),
        m_locationId (0),
        m_lockManagedObject (NULL)
{
}

LockManagementMessagingContext::~LockManagementMessagingContext ()
{
    if (m_lockManagedObject)
    {
        delete (m_lockManagedObject);
        m_lockManagedObject = NULL;
    }
}

LocationId LockManagementMessagingContext::getLocationId () const
{
    return (m_locationId);
}

const string& LockManagementMessagingContext::getServiceString () const
{
    return (m_serviceString);
}

LockManagedObject* LockManagementMessagingContext::getPLockManagedObject () const
{
    return (m_lockManagedObject);
}

void LockManagementMessagingContext::setLocationId (const LocationId locationId)
{
    m_locationId = locationId;
}

void LockManagementMessagingContext::setServiceString (const string &serviceString)
{
    m_serviceString = serviceString;
}

void LockManagementMessagingContext::setPLockManagedObject (LockManagedObject *lockManagedObject)
{
    m_lockManagedObject = lockManagedObject;
}

}


