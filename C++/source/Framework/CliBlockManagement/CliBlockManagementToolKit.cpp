/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/CliBlockManagement/CliBlockManagementToolKit.h"
#include "Framework/Utils/TraceUtils.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include <sstream>

namespace WaveNs
{

map <ResourceId, CliBlockDetail>                  CliBlockManagementToolKit::m_cliBlockMap;
PrismMutex                                        CliBlockManagementToolKit::m_cliBlockMapMutex;
PrismMutex                                        CliBlockManagementToolKit::m_cliBlockOperationMutex;

ResourceId CliBlockManagementToolKit::blockCli (const CliBlockDetail &detail)
{

    ResourceId reason = (detail.getCliBlockContext ()).getReason ();

    m_cliBlockMapMutex.lock (); 

    map<ResourceId, CliBlockDetail>::iterator element          = m_cliBlockMap.find (reason);  
    map<ResourceId, CliBlockDetail>::iterator endElement       = m_cliBlockMap.end ();

    if (endElement == element)
    {
        m_cliBlockMap [reason] = detail; 
        WaveNs::trace (TRACE_LEVEL_INFO, string ("CliBlockManagementToolKit::blockCli : service [" + FrameworkToolKit::getServiceNameById (detail.getWaveServiceId ()) + "] successfully block cli for reason [" + reason + "].")); 
    }
    else
    {
        // Can't block CLI for the same reason
        WaveNs::trace (TRACE_LEVEL_ERROR, string ("CliBlockManagementToolKit::blockCli : service [" + FrameworkToolKit::getServiceNameById (detail.getWaveServiceId ()) + "] failed to block cli for reason [" + reason + "].")); 
    }
 
    m_cliBlockMapMutex.unlock ();  

    return WAVE_MESSAGE_SUCCESS;
}

ResourceId CliBlockManagementToolKit::unblockCli (const CliBlockDetail &detail)
{

    ResourceId reason = (detail.getCliBlockContext ()).getReason ();

    m_cliBlockMapMutex.lock (); 

    map<ResourceId, CliBlockDetail>::iterator element          = m_cliBlockMap.find (reason);
    map<ResourceId, CliBlockDetail>::iterator endElement       = m_cliBlockMap.end ();

    if (endElement == element)
    {
        // Can't unblock CLI which was not blocked before
        WaveNs::trace (TRACE_LEVEL_ERROR, string ("CliBlockManagementToolKit::unblockCli : service [" + FrameworkToolKit::getServiceNameById (detail.getWaveServiceId ()) + "] failed to unblock cli for reason [" + reason + "]."));
    }
    else
    {
        m_cliBlockMap.erase (reason);
        WaveNs::trace (TRACE_LEVEL_INFO, string ("CliBlockManagementToolKit::unblockCli : service [" + FrameworkToolKit::getServiceNameById (detail.getWaveServiceId ()) + "] successfully unblock cli for reason [" + reason + "]."));
    }
 
    m_cliBlockMapMutex.unlock ();  

    return WAVE_MESSAGE_SUCCESS;
}

bool CliBlockManagementToolKit::isCliBlocked (vector<ResourceId> &reasons)
{

    bool blocked = false;

    m_cliBlockMapMutex.lock ();

    if (!m_cliBlockMap.empty ())
    {

        reasons.clear ();
        map<ResourceId, CliBlockDetail>::iterator it;
        for (it = m_cliBlockMap.begin(); it != m_cliBlockMap.end(); ++it)
        {
            reasons.push_back (it->first);
        }

        blocked = true;
    }
    else
    {
        blocked = false; 
    }

    m_cliBlockMapMutex.unlock ();

    return blocked;
}

ResourceId CliBlockManagementToolKit::getCliBlockDetail (const ResourceId givenReason, CliBlockDetail &detail)
{
    
    ResourceId status = WAVE_MESSAGE_ERROR;   

    m_cliBlockMapMutex.lock (); 

    map<ResourceId, CliBlockDetail>::iterator element          = m_cliBlockMap.find (givenReason);  
    map<ResourceId, CliBlockDetail>::iterator endElement       = m_cliBlockMap.end ();

    if (endElement == element)
    {
        // Can't find given reason
        status = WAVE_MESSAGE_ERROR;
    }
    else
    {
        detail = element->second; 
        status = WAVE_MESSAGE_SUCCESS;
    }
 
    m_cliBlockMapMutex.unlock ();  

    return status;
          
}

ResourceId CliBlockManagementToolKit::cleanAllBlockedReasons ()
{

    m_cliBlockMapMutex.lock ();
    m_cliBlockMap.clear ();
    m_cliBlockMapMutex.unlock ();

    return WAVE_MESSAGE_SUCCESS; 
}

string CliBlockManagementToolKit::getDisplayString ()
{

    string description = "Cli Block Details:\n==================\n";

    m_cliBlockMapMutex.lock ();

    map<ResourceId, CliBlockDetail>::iterator it;

    for (it = m_cliBlockMap.begin(); it != m_cliBlockMap.end(); ++it)
    {
        stringstream convert;
        convert << (it->second).getOriginator ();
        string locationString = convert.str();

        description += string ("reasonCode:"                    + FrameworkToolKit::localizeToSourceCodeEnum (it->first)                                               + "\n");
        description += string ("    reasonDescription:"         + FrameworkToolKit::localize (it->first)                                                               + "\n");
        description += string ("    originatorLocationId:"      + locationString                                                                                       + "\n");
        description += string ("    originatorServiceName:"     + FrameworkToolKit::getServiceNameById ((it->second).getWaveServiceId ())                             + "\n\n");
    }

    m_cliBlockMapMutex.unlock ();

    return description;
}

PrismMutexStatus CliBlockManagementToolKit::tryLock ()
{
    return m_cliBlockOperationMutex.tryLock ();
}

PrismMutexStatus CliBlockManagementToolKit::unlock ()
{
    return m_cliBlockOperationMutex.unlock ();
}

PrismMutexStatus CliBlockManagementToolKit::lock ()
{
    return m_cliBlockOperationMutex.lock ();
}


}
