/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#include "Framework/Core/WaveServiceMap.h"
#include "Framework/MultiThreading/WaveThread.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

WaveServiceMap::WaveServiceMap ()
{
}

WaveServiceMap::~WaveServiceMap ()
{
}

void WaveServiceMap::addServiceMap  (WaveServiceId id, WaveThread *pWaveThread, const string &serviceName)
{
    m_mutex.lock ();

    WaveThread    *pTempWaveThread   = m_servicesMap[id];
    WaveServiceId  tempWaveServiceId = m_servicesIdMap[serviceName];

    if (NULL != pTempWaveThread)
    {
        waveAssert (false, __FILE__, __LINE__);
        cerr << "Cannot proceed.  Trying to add a duplicate service id." << endl;
        exit (0);
    }

    if (0 != tempWaveServiceId)
    {
        waveAssert (false, __FILE__, __LINE__);
        cerr << "Cannot proceed.  Trying to add a duplicate service name." << endl;
        exit (0);
    }

    m_servicesMap[id]            = pWaveThread;
    m_servicesNameMap[id]        = serviceName;
    m_servicesIdMap[serviceName] = id;

    m_mutex.unlock ();
}

void WaveServiceMap::removeServiceMap (WaveServiceId id)
{
    map<WaveServiceId, WaveThread *>::iterator  element      = m_servicesMap.find (id);
    map<WaveServiceId, WaveThread *>::iterator  endElement   = m_servicesMap.end  ();

    WaveThread                                  *pWaveThread = NULL;

    if (endElement != element)
    {
        pWaveThread = element->second;

        waveAssert (NULL != pWaveThread, __FILE__, __LINE__);

        m_servicesMap.erase (element);
    }

    map<WaveServiceId, string>::iterator element1     = m_servicesNameMap.find (id);
    map<WaveServiceId, string>::iterator endElement1  = m_servicesNameMap.end  ();

    string                                serviceName;

    if (endElement1 != element1)
    {
        serviceName = element1->second;

        waveAssert (NULL != pWaveThread, __FILE__, __LINE__);

        m_servicesNameMap.erase (element1);
    }

    map<string, WaveServiceId>::iterator element2    = m_servicesIdMap.find (serviceName);
    map<string, WaveServiceId>::iterator endElement2 = m_servicesIdMap.end  ();

    if (endElement2 != element2)
    {
        waveAssert (id == element2->second, __FILE__, __LINE__);

        m_servicesIdMap.erase (element2);
    }

    m_mutex.unlock ();
}

WaveThread *WaveServiceMap::getWaveThreadForServiceId (WaveServiceId id)
{
    m_mutex.lock ();

    map<WaveServiceId, WaveThread *>::iterator  element    = m_servicesMap.find (id);
    map<WaveServiceId, WaveThread *>::iterator  end        = m_servicesMap.end ();
    WaveThread                                *pWaveThread = NULL;

    if (end != element)
    {
        pWaveThread = element->second;
    }

    m_mutex.unlock ();

    return (pWaveThread);
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

    map<WaveServiceId, WaveThread *>::iterator  element         = m_servicesMap.begin ();
    map<WaveServiceId, WaveThread *>::iterator  limitingElement = m_servicesMap.end ();
    WaveThread                                *pWaveThread      = NULL;

    while (element != limitingElement)
    {
        pWaveThread = element->second;
        pWaveThread->joinCallingThread ();
        element++;
    }

    m_mutex.unlock ();

    return (WAVE_THREAD_SUCCESS);
}

}
