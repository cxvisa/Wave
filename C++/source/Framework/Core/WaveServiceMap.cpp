/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Core/WaveServiceMap.h"
#include "Framework/MultiThreading/PrismThread.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveServiceMap::WaveServiceMap ()
{
}

WaveServiceMap::~WaveServiceMap ()
{
}

void WaveServiceMap::addServiceMap  (WaveServiceId id, PrismThread *pPrismThread, const string &serviceName)
{
    m_mutex.lock ();

    PrismThread    *pTempPrismThread   = m_servicesMap[id];
    WaveServiceId  tempWaveServiceId = m_servicesIdMap[serviceName];

    if (NULL != pTempPrismThread)
    {
        prismAssert (false, __FILE__, __LINE__);
        cerr << "Cannot proceed.  Trying to add a duplicate service id." << endl;
        exit (0);
    }

    if (0 != tempWaveServiceId)
    {
        prismAssert (false, __FILE__, __LINE__);
        cerr << "Cannot proceed.  Trying to add a duplicate service name." << endl;
        exit (0);
    }

    m_servicesMap[id]            = pPrismThread;
    m_servicesNameMap[id]        = serviceName;
    m_servicesIdMap[serviceName] = id;

    m_mutex.unlock ();
}

void WaveServiceMap::removeServiceMap (WaveServiceId id)
{
    map<WaveServiceId, PrismThread *>::iterator  element      = m_servicesMap.find (id);
    map<WaveServiceId, PrismThread *>::iterator  endElement   = m_servicesMap.end  ();

    PrismThread                                  *pPrismThread = NULL;

    if (endElement != element)
    {
        pPrismThread = element->second;

        prismAssert (NULL != pPrismThread, __FILE__, __LINE__);

        m_servicesMap.erase (element);
    }

    map<WaveServiceId, string>::iterator element1     = m_servicesNameMap.find (id);
    map<WaveServiceId, string>::iterator endElement1  = m_servicesNameMap.end  ();

    string                                serviceName;

    if (endElement1 != element1)
    {
        serviceName = element1->second;

        prismAssert (NULL != pPrismThread, __FILE__, __LINE__);

        m_servicesNameMap.erase (element1);
    }

    map<string, WaveServiceId>::iterator element2    = m_servicesIdMap.find (serviceName);
    map<string, WaveServiceId>::iterator endElement2 = m_servicesIdMap.end  ();

    if (endElement2 != element2)
    {
        prismAssert (id == element2->second, __FILE__, __LINE__);

        m_servicesIdMap.erase (element2);
    }

    m_mutex.unlock ();
}

PrismThread *WaveServiceMap::getPrismThreadForServiceId (WaveServiceId id)
{
    m_mutex.lock ();

    map<WaveServiceId, PrismThread *>::iterator  element    = m_servicesMap.find (id);
    map<WaveServiceId, PrismThread *>::iterator  end        = m_servicesMap.end ();
    PrismThread                                *pPrismThread = NULL;

    if (end != element)
    {
        pPrismThread = element->second;
    }

    m_mutex.unlock ();

    return (pPrismThread);
}

void WaveServiceMap::getListOfServiceIds (vector<WaveServiceId> &serviceIds)
{
    m_mutex.lock ();

    map<WaveServiceId, string>::iterator element      = m_servicesNameMap.begin ();
    map<WaveServiceId, string>::iterator end          = m_servicesNameMap.end ();

    serviceIds.clear ();

    while (element != end)
    {
        serviceIds.push_back (element->first);
        element++;
    }

    m_mutex.unlock ();

    return;
}

string WaveServiceMap::getPrismServiceNameForServiceId (const WaveServiceId &id)
{
    m_mutex.lock ();

    map<WaveServiceId, string>::iterator element      = m_servicesNameMap.find (id);
    map<WaveServiceId, string>::iterator end          = m_servicesNameMap.end ();
    string                                serviceName;

    if (end != element)
    {
        serviceName = element->second;
    }

    m_mutex.unlock ();

    return (serviceName);
}

WaveServiceId WaveServiceMap::getWaveServiceIdForServiceName (const string &serviceName)
{
    m_mutex.lock ();

    map<string, WaveServiceId>::iterator element   = m_servicesIdMap.find (serviceName);
    map<string, WaveServiceId>::iterator end       = m_servicesIdMap.end ();
    WaveServiceId                        serviceId = 0;

    if (end != element)
    {
        serviceId = element->second;
    }

    m_mutex.unlock ();

    return (serviceId);
}

WaveThreadStatus WaveServiceMap::joinAllThreads ()
{
    m_mutex.lock ();

    map<WaveServiceId, PrismThread *>::iterator  element         = m_servicesMap.begin ();
    map<WaveServiceId, PrismThread *>::iterator  limitingElement = m_servicesMap.end ();
    PrismThread                                *pPrismThread      = NULL;

    while (element != limitingElement)
    {
        pPrismThread = element->second;
        pPrismThread->joinCallingThread ();
        element++;
    }

    m_mutex.unlock ();

    return (WAVE_THREAD_SUCCESS);
}

}
