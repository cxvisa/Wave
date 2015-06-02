/***************************************************************************
 *   Copyright (C) 2008-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveSendMulticastContext.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveSendMulticastContext::WaveSendMulticastContext (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_pPrismMessage (NULL),
      m_multicastStatus (WAVE_MESSAGE_SUCCESS)
{
    FrameworkToolKit::getFullyConnectedLocations (m_connectedLocationIds);
    m_connectedLocationIds.push_back (FrameworkToolKit::getThisLocationId ());
}

WaveSendMulticastContext::~WaveSendMulticastContext ()
{
    if (NULL != m_pPrismMessage)
    {
        delete m_pPrismMessage;
    }
}

void WaveSendMulticastContext::setPrismMessage (PrismMessage *pPrismMessage)
{
    m_pPrismMessage = pPrismMessage;
}

PrismMessage *WaveSendMulticastContext::getPrismMessage ()
{
    return (m_pPrismMessage);
}

void WaveSendMulticastContext::setAllLocationsToSent (vector<LocationId> &locationIds)
{
    m_connectedLocationIds = locationIds;
}

vector<LocationId> WaveSendMulticastContext::getAllLocationsToSent () const
{
    return (m_connectedLocationIds);
}

void WaveSendMulticastContext::setStatusForALocation (LocationId &locationId, ResourceId &locationStatus)
{
    UI32 numberOfLocations = m_connectedLocationIds.size ();
    bool validLocation     = false;

    for (UI32 i = 0; i < numberOfLocations; i++)
    {
        if (locationId == m_connectedLocationIds [i])
        {
            validLocation = true;
        }
    }
    
    prismAssert (false != validLocation, __FILE__, __LINE__);

    m_locationStatus [locationId] = locationStatus;
}

ResourceId WaveSendMulticastContext::getStatusForALocation (LocationId &locationId)
{
    map<LocationId, ResourceId>::iterator element    = m_locationStatus.find (locationId);
    map<LocationId, ResourceId>::iterator endElement = m_locationStatus.end ();

    if (element == endElement)
    {
        prismAssert (false, __FILE__, __LINE__);
    }

    return (m_locationStatus [locationId]);
}

ResourceId WaveSendMulticastContext::getOverallMulticastStatus ()
{
    return (m_multicastStatus);
}

void  WaveSendMulticastContext::setMulticastStatus (ResourceId &status)
{
    m_multicastStatus = status;
}

}
