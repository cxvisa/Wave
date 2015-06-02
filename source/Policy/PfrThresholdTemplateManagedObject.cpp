/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThresholdTemplateManagedObject.h"
#include "Policy/PolicyObjectManager.h"
#include "Framework/Attributes/Attributes.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

PfrThresholdTemplateManagedObject::PfrThresholdTemplateManagedObject (PolicyObjectManager *pPolicyObjectManager)
    : PrismElement (pPolicyObjectManager),
      PrismPersistableObject (PfrThresholdTemplateManagedObject::getClassName (), WaveManagedObject::getClassName ()),
      WaveManagedObject (pPolicyObjectManager)
{
    setEmptyNeededOnPersistentBoot (true);
    setEmptyNeededOnPersistentBootWithDefault (false);
}

PfrThresholdTemplateManagedObject::~PfrThresholdTemplateManagedObject ()
{
}

string PfrThresholdTemplateManagedObject::getClassName ()
{
    return ("PfrThresholdTemplateManagedObject");
}

void PfrThresholdTemplateManagedObject::setupAttributesForPersistence ()
{
    WaveManagedObject::setupAttributesForPersistence ();

    addPersistableAttribute (new AttributeSI32 (&m_lossRate,            "lossRate"));
    addPersistableAttribute (new AttributeSI32 (&m_oneWayDelay,         "oneWayDelay"));
    addPersistableAttribute (new AttributeSI32 (&m_jitter,              "jitter"));
    addPersistableAttribute (new AttributeSI32 (&m_lossRatePriority,    "lossRatePriority"));
    addPersistableAttribute (new AttributeSI32 (&m_oneWayDelayPriority, "oneWayDelayPriority"));
    addPersistableAttribute (new AttributeSI32 (&m_jitterPriority,      "jitterPriority"));
}

void PfrThresholdTemplateManagedObject::setupAttributesForCreate ()
{
    WaveManagedObject::setupAttributesForCreate ();

    addPersistableAttributeForCreate (new AttributeSI32 (&m_lossRate,            "lossRate"));
    addPersistableAttributeForCreate (new AttributeSI32 (&m_oneWayDelay,         "oneWayDelay"));
    addPersistableAttributeForCreate (new AttributeSI32 (&m_jitter,              "jitter"));
    addPersistableAttributeForCreate (new AttributeSI32 (&m_lossRatePriority,    "lossRatePriority"));
    addPersistableAttributeForCreate (new AttributeSI32 (&m_oneWayDelayPriority, "oneWayDelayPriority"));
    addPersistableAttributeForCreate (new AttributeSI32 (&m_jitterPriority,      "jitterPriority"));
}

void PfrThresholdTemplateManagedObject::setupKeys ()
{
    vector<string> userDefinedKeyCombination;

    userDefinedKeyCombination.push_back ("name");

    setUserDefinedKeyCombination (userDefinedKeyCombination);
}

SI32 PfrThresholdTemplateManagedObject::getLossRate () const
{
    return (m_lossRate);
}

void PfrThresholdTemplateManagedObject::setLossRate (const SI32 &lossRate)
{
    m_lossRate = lossRate;
}

SI32 PfrThresholdTemplateManagedObject::getOneWayDelay () const
{
    return (m_oneWayDelay);
}

void PfrThresholdTemplateManagedObject::setOneWayDelay (const SI32 &oneWayDelay)
{
    m_oneWayDelay = oneWayDelay;
}

SI32 PfrThresholdTemplateManagedObject::getJitter () const
{
    return (m_jitter);
}

void PfrThresholdTemplateManagedObject::setJitter (const SI32 &jitter)
{
    m_jitter = jitter;
}

SI32 PfrThresholdTemplateManagedObject::getLossRatePriority () const
{
    return (m_lossRatePriority);
}

void PfrThresholdTemplateManagedObject::setLossRatePriority (const SI32 &lossRatePriority)
{
    m_lossRatePriority = lossRatePriority;
}

SI32 PfrThresholdTemplateManagedObject::getOneWayDelayPriority () const
{
    return (m_oneWayDelayPriority);
}

void PfrThresholdTemplateManagedObject::setOneWayDelayPriority (const SI32 &oneWayDelayPriority)
{
    m_oneWayDelayPriority = oneWayDelayPriority;
}

SI32 PfrThresholdTemplateManagedObject::getJitterPriority () const
{
    return (m_jitterPriority);
}

void PfrThresholdTemplateManagedObject::setJitterPriority (const SI32 &jitterPriority)
{
    m_jitterPriority = jitterPriority;
}

}

