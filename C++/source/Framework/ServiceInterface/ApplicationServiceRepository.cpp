/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ServiceInterface/ApplicationServiceRepository.h"
#include "Framework/ServiceInterface/ApplicationService.h"
#include "Framework/ServiceInterface/ApplicationLocalService.h"
#include "Framework/Core/FrameworkSequenceGenerator.h"
#include "Framework/Core/WaveFrameworkObjectManager.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"


namespace WaveNs
{

ApplicationServiceRepository::ApplicationServiceRepository ()
{
}

ApplicationServiceRepository::~ApplicationServiceRepository ()
{
}

void ApplicationServiceRepository::addNewApplicationService (const UI32 &newApplicationServiceId, const string &newApplicationServiceName)
{
    map<UI32, string>::iterator element    = m_applicationServiceNamesMap.find (newApplicationServiceId);
    map<UI32, string>::iterator endElement = m_applicationServiceNamesMap.end ();

    if (element != endElement)
    {
        trace (TRACE_LEVEL_FATAL, string ("ApplicationServiceRepository::addApplicationService : Application Service ID (") + newApplicationServiceId + ") already exists in the map");

        waveAssert (false, __FILE__, __LINE__);
    }

    if (0 == (strcmp ("", (newApplicationServiceName.c_str ()))))
    {
        trace (TRACE_LEVEL_FATAL, "ApplicationServiceRepository::addApplicationService : NULL Service name is not allowed.");

        waveAssert (false, __FILE__, __LINE__);
    }

    m_applicationServiceNamesMap[newApplicationServiceId] = newApplicationServiceName;
}

void ApplicationServiceRepository::addNewApplicationLocalService (const UI32 &newApplicationLocalServiceId, const string &newApplicationLocalServiceName)
{
    map<UI32, string>::iterator element    = m_applicationLocalServiceNamesMap.find (newApplicationLocalServiceId);
    map<UI32, string>::iterator endElement = m_applicationLocalServiceNamesMap.end ();

    if (element != element)
    {
        trace (TRACE_LEVEL_FATAL, string ("ApplicationServiceRepository::addNewApplicationLocalService : Application Service ID (") + newApplicationLocalServiceId + ") already exists in the map");

        waveAssert (false, __FILE__, __LINE__);
    }

    if (0 == (strcmp ("", (newApplicationLocalServiceName.c_str ()))))
    {
        trace (TRACE_LEVEL_FATAL, "ApplicationServiceRepository::addNewApplicationLocalService : NULL Service name is not allowed.");

        waveAssert (false, __FILE__, __LINE__);
    }

    m_applicationLocalServiceNamesMap[newApplicationLocalServiceId] = newApplicationLocalServiceName;
}

ApplicationService *ApplicationServiceRepository::getApplicationService (const UI32 &applicationServiceId)
{
    return (m_applicationServicesMap[applicationServiceId]);
}

ApplicationLocalService *ApplicationServiceRepository::getApplicationLocalService (const UI32 &applicationLocalServiceId)
{
    return (m_applicationLocalServicesMap[applicationLocalServiceId]);
}

bool ApplicationServiceRepository::isAnApplicationLocalService (const UI32 &applicationLocalServiceId)
{
    map<UI32, ApplicationLocalService *>::iterator element    = m_applicationLocalServicesMap.find (applicationLocalServiceId);
    map<UI32, ApplicationLocalService *>::iterator endElement = m_applicationLocalServicesMap.end ();

    if (element != endElement)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void ApplicationServiceRepository::createApplicationServices ()
{
    map<UI32, string>::iterator element    = m_applicationServiceNamesMap.begin ();
    map<UI32, string>::iterator endElement = m_applicationServiceNamesMap.end ();

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();

    while (element != endElement)
    {
        waveAssert (NULL == m_applicationServicesMap[element->first], __FILE__, __LINE__);

        ApplicationService *pNewApplicationService = new ApplicationService (element->second, element->first);

        waveAssert (NULL != pNewApplicationService, __FILE__, __LINE__);

        m_applicationServicesMap[element->first] = pNewApplicationService;

        // Add the New Application Service into all the Framework Sequencers.

        frameworkSequenceGenerator.addWaveServiceIdToAll (pNewApplicationService->getServiceId ());

        element++;
    }
}

void ApplicationServiceRepository::createApplicationLocalServices ()
{
    map<UI32, string>::iterator element    = m_applicationLocalServiceNamesMap.begin ();
    map<UI32, string>::iterator endElement = m_applicationLocalServiceNamesMap.end ();

    FrameworkSequenceGenerator &frameworkSequenceGenerator = WaveFrameworkObjectManager::getCurrentFrameworkSequenceGenerator ();

    while (element != endElement)
    {
        waveAssert (NULL == m_applicationLocalServicesMap[element->first], __FILE__, __LINE__);

        ApplicationLocalService *pNewApplicationLocalService = new ApplicationLocalService (element->second, element->first);

        waveAssert (NULL != pNewApplicationLocalService, __FILE__, __LINE__);

        m_applicationLocalServicesMap[element->first] = pNewApplicationLocalService;

        // Add the New Application Service into all the Framework Sequencers.

        frameworkSequenceGenerator.addWaveServiceIdToAll (pNewApplicationLocalService->getServiceId ());

        element++;
    }
}

ApplicationServiceRepository *ApplicationServiceRepository::getInstance ()
{
    static ApplicationServiceRepository *pApplicationServiceRepository = new ApplicationServiceRepository ();

    return (pApplicationServiceRepository);
}

void ApplicationServiceRepository::getApplicationServiceIds (vector<UI32> &applicationServiceIds)
{
    map<UI32, string>::iterator element    = m_applicationServiceNamesMap.begin ();
    map<UI32, string>::iterator endElement = m_applicationServiceNamesMap.end ();

    while (element != endElement)
    {
        applicationServiceIds.push_back (element->first);
        element++;
    }
}

void ApplicationServiceRepository::getApplicationLocalServiceIds (vector<UI32> &applicationLocalServiceIds)
{
    map<UI32, string>::iterator element    = m_applicationLocalServiceNamesMap.begin ();
    map<UI32, string>::iterator endElement = m_applicationLocalServiceNamesMap.end ();

    while (element != endElement)
    {
        applicationLocalServiceIds.push_back (element->first);
        element++;
    }
}

}
