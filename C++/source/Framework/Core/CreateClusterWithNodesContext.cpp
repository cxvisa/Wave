/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Core/CreateClusterWithNodesContext.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

CreateClusterWithNodesContext::CreateClusterWithNodesContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pWaveMessage, pWaveElement, pSteps, numberOfSteps), m_isDeletion(false)
{
    m_isCreateClusterContext = false;
}

CreateClusterWithNodesContext::CreateClusterWithNodesContext (PrismAsynchronousContext *pPrismAsynchronousContext, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext (pPrismAsynchronousContext, pWaveElement, pSteps, numberOfSteps),m_isDeletion(false)
{
    m_isCreateClusterContext = false;
}

CreateClusterWithNodesContext::~CreateClusterWithNodesContext ()
{
}

bool CreateClusterWithNodesContext::doesLocationExist (const LocationId &locationId)
{
    vector<LocationId>::iterator element = m_newLocationIdsVector.begin ();
    vector<LocationId>::iterator end     = m_newLocationIdsVector.end ();

    while (end != element)
    {
        if (locationId == (*element))
        {
            return (true);
        }

        element++;
    }

    return (false);
}

void CreateClusterWithNodesContext::addNewLocationId (const LocationId &locationId)
{
    if (false == (doesLocationExist (locationId)))
    {
        m_newLocationIdsVector.push_back (locationId);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, "CreateClusterWithNodesContext::addNewLocationId : Trying to add already existing location.");
        waveAssert (false, __FILE__, __LINE__);
    }
}

void CreateClusterWithNodesContext::removeNewLocationId (const LocationId &locationId)
{
    vector<LocationId>::iterator element = m_newLocationIdsVector.begin ();
    vector<LocationId>::iterator end     = m_newLocationIdsVector.end ();

    while (end != element)
    {
        if (locationId == (*element))
        {
            m_newLocationIdsVector.erase (element);
            return;
        }

        element++;
    }

    trace (TRACE_LEVEL_FATAL, "CreateClusterWithNodesContext::removeNewLocationId : Trying to remove non-existing location.");
    waveAssert (false, __FILE__, __LINE__);
}

LocationId CreateClusterWithNodesContext::getNewLocationIdAt (const UI32 &i)
{
    if (i < (m_newLocationIdsVector.size ()))
    {
        return (m_newLocationIdsVector[i]);
    }
    else
    {
        trace (TRACE_LEVEL_FATAL, string ("CreateClusterWithNodesContext::getNewLocationIdAt : Index (") + i + ") is out of range (" + m_newLocationIdsVector.size () + ").");
        waveAssert (false, __FILE__, __LINE__);
        return (0);
    }
}

UI32 CreateClusterWithNodesContext::getNumberOfNewLocationIds ()
{
    return (m_newLocationIdsVector.size ());
}

void CreateClusterWithNodesContext::addValidationDetailsForService (const WaveServiceId &waveServiceId, void *pValidationDetials, const UI32 size)
{
    m_waveServiceIdsVector.push_back        (waveServiceId);
    m_validationDetailsVector.push_back      (pValidationDetials);
    m_validationDetailsSizesVector.push_back (size);
}

vector<WaveServiceId> &CreateClusterWithNodesContext::getWaveServiceIdsVector ()
{
    return (m_waveServiceIdsVector);
}

vector<void *> &CreateClusterWithNodesContext::getValidationDetailsVector ()
{
    return (m_validationDetailsVector);
}

vector<UI32> &CreateClusterWithNodesContext::getValidationDetailsSizesVector ()
{
    return (m_validationDetailsSizesVector);
}

void CreateClusterWithNodesContext::addValidaionResultsLocation (const string &ipAddress, const SI32 &port)
{
    m_prismLocationIpAddressesForValidationResultsVector.push_back (ipAddress);
    m_prismLocationPortsForValidationResultsVector.push_back (port);
}

UI32 CreateClusterWithNodesContext::getNumberOfResultsLocations ()
{
    waveAssert (m_prismLocationIpAddressesForValidationResultsVector.size () == m_prismLocationPortsForValidationResultsVector.size (), __FILE__, __LINE__);

    return (m_prismLocationIpAddressesForValidationResultsVector.size ());
}

void CreateClusterWithNodesContext::getResultsLocationAt (const UI32 &i, string &ipAddress, SI32 &port)
{
    ipAddress = "";
    port      = 0;

    if (i < getNumberOfResultsLocations ())
    {
        ipAddress = m_prismLocationIpAddressesForValidationResultsVector[i];
        port      = m_prismLocationPortsForValidationResultsVector[i];
    }
}

void CreateClusterWithNodesContext::addValidationResultsForService (const string &ipAddress, const SI32 &port, const WaveServiceId &waveServiceId, void *const &pValidationResults, const UI32 &validationResultsSize)
{
    string uniqueIdString = ipAddress + string (":") + port + string (":") + waveServiceId;

    m_prismLocationValidationResultsVector[uniqueIdString]      = pValidationResults;
    m_prismLocationValidationResultsSizesVector[uniqueIdString] = validationResultsSize;
}

void CreateClusterWithNodesContext::getValidationResultsForService (const string &ipAddress, const SI32 &port, const WaveServiceId &waveServiceId, void *&pValidationResults, UI32 &validationResultsSize)
{
    string uniqueIdString = ipAddress + string (":") + port + string (":") + waveServiceId;

    pValidationResults    = NULL;
    validationResultsSize = 0;

    map<string, void *>::iterator validationResultsElement = m_prismLocationValidationResultsVector.find (uniqueIdString);
    map<string, void *>::iterator validationResultsEnd     = m_prismLocationValidationResultsVector.end ();

    if (validationResultsElement != validationResultsEnd)
    {
        pValidationResults = validationResultsElement->second;
    }
    else
    {
        return;
    }

    map<string, UI32>::iterator validationResultsSizeElement = m_prismLocationValidationResultsSizesVector.find (uniqueIdString);
    map<string, UI32>::iterator validationResultsSizeEnd     = m_prismLocationValidationResultsSizesVector.end ();

    if (validationResultsSizeElement != validationResultsSizeEnd)
    {
        validationResultsSize = validationResultsSizeElement->second;
    }
    else
    {
        // We found the validation results but could not find the size of the validation results.  This must not happen.
        waveAssert (false, __FILE__, __LINE__);
    }
}

vector<WaveServiceId> &CreateClusterWithNodesContext::getWaveServiceIdsToCommunicate ()
{
    return (m_waveServiceIdsToCommunicate);
}

bool CreateClusterWithNodesContext::getIsDeletion ()    const
{
    return m_isDeletion;
}
void  CreateClusterWithNodesContext::setIsDeletion (bool deletion)
{
    m_isDeletion = deletion;
}

void CreateClusterWithNodesContext::addToSuccessfullyAddedLocationIdVector (LocationId locationId)
{
    m_successfullyAddedLocationIdVector.push_back (locationId);
}

vector<LocationId> CreateClusterWithNodesContext::getSuccessfullyAddedLocationIdVector () const
{
    return (m_successfullyAddedLocationIdVector);
}

void CreateClusterWithNodesContext::addToFailedLocationIdVector (LocationId locationId)
{
    if (isAFailedLocation (locationId))
    {
        return;
    }
   
    m_failedLocationIds.push_back (locationId); 
}

vector<LocationId> CreateClusterWithNodesContext::getFailedLocationIdVector () const
{
    return (m_failedLocationIds);
}

bool CreateClusterWithNodesContext::isAFailedLocation (LocationId locationId)
{
    vector<WaveServiceId>::iterator element = m_failedLocationIds.begin ();
    vector<WaveServiceId>::iterator end     = m_failedLocationIds.end ();

    while (end != element)
    {
        if (locationId == (*element))
        {
            return (true);
        }

        element++;
    }

    return (false);
}

void CreateClusterWithNodesContext::clearFailedLocationIdVector ()
{
    m_failedLocationIds.clear ();
}

bool CreateClusterWithNodesContext::getIsCreateClusterContext () const
{
    return (m_isCreateClusterContext);
}

void CreateClusterWithNodesContext::setIsCreateClusterContext (const bool &isCreateClusterContext)
{
    m_isCreateClusterContext = isCreateClusterContext;
}

}
