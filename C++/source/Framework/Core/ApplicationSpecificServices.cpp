/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#include "Framework/Core/ApplicationSpecificServices.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{

ApplicationSpecificServices::ApplicationSpecificServices ()
{
}

ApplicationSpecificServices::~ApplicationSpecificServices ()
{
}

ApplicationSpecificServices *ApplicationSpecificServices::getInstance ()
{
    static ApplicationSpecificServices *pApplicationSpecificServices = NULL;

    if (NULL == pApplicationSpecificServices)
    {
        pApplicationSpecificServices = new ApplicationSpecificServices ();
        WaveNs::waveAssert (NULL != pApplicationSpecificServices, __FILE__, __LINE__);
    }

    return (pApplicationSpecificServices);
}

void ApplicationSpecificServices::setWaveServiceId (WaveServiceId waveServiceId)
{
    m_WaveServiceId.push_back (waveServiceId);
}

bool ApplicationSpecificServices::isApplicationSpecificServiceId (WaveServiceId waveServiceId)
{
    vector<WaveServiceId>::iterator element = m_WaveServiceId.begin ();
    vector<WaveServiceId>::iterator end     = m_WaveServiceId.end ();

    while (end != element)
    {
        if (waveServiceId == (*element))
        {
            return (true);
        }
        
        element++;
    }

    return (false);
}

}


