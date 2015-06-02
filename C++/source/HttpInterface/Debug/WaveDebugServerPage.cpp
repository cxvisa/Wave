/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/Debug/WaveDebugServerPage.h"
#include "HttpInterface/Debug/Trace/WaveTraceServerMultiPage.h"

namespace WaveNs
{

WaveDebugServerPage::WaveDebugServerPage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path)
    : WaveServerPage(pHttpInterfaceReceiverObjectManager, path)
{
    m_pWaveTraceServerMultiPage = new WaveTraceServerMultiPage (pHttpInterfaceReceiverObjectManager, "/debug/trace");

    prismAssert (NULL != m_pWaveTraceServerMultiPage, __FILE__, __LINE__);
}

WaveDebugServerPage::~WaveDebugServerPage ()
{
    if (NULL != m_pWaveTraceServerMultiPage)
    {
        delete m_pWaveTraceServerMultiPage;
    }
}

}
