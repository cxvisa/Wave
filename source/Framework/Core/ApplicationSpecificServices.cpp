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
        WaveNs::prismAssert (NULL != pApplicationSpecificServices, __FILE__, __LINE__);
    }

    return (pApplicationSpecificServices);
}

void ApplicationSpecificServices::setPrismServiceId (PrismServiceId prismServiceId)
{
    m_PrismServiceId.push_back (prismServiceId);
}

bool ApplicationSpecificServices::isApplicationSpecificServiceId (PrismServiceId prismServiceId)
{
    vector<PrismServiceId>::iterator element = m_PrismServiceId.begin ();
    vector<PrismServiceId>::iterator end     = m_PrismServiceId.end ();

    while (end != element)
    {
        if (prismServiceId == (*element))
        {
            return (true);
        }
        
        element++;
    }

    return (false);
}

}


