/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/WaveServerPageDirectory.h"
#include <Framework/Utils/AssertUtils.h>
#include "Framework/Utils/TraceUtils.h"
#include <Framework/Core/Wave.h>
#include "HttpInterface/WaveServerPage.h"
#include "HttpInterface/WaveServerPageDirectoryEntry.h"

namespace WaveNs
{

map<string, WaveServerPage *> WaveServerPageDirectory::m_serverPageMap;
WaveServerPageDirectoryEntry  WaveServerPageDirectory::m_waveServerPageDirectoryRoot ("/", NULL);

WaveServerPageDirectory::WaveServerPageDirectory ()
{
}

WaveServerPageDirectory::~WaveServerPageDirectory ()
{
}

bool WaveServerPageDirectory::isAKnownServerPage (const string& path)
{
    map<string, WaveServerPage *>::const_iterator element    = m_serverPageMap.find (path);
    map<string, WaveServerPage *>::const_iterator endElement = m_serverPageMap.end  ();

    if (endElement != element)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void WaveServerPageDirectory::registerServerPage (WaveServerPage *pWaveServerPage)
{
    prismAssert (NULL != pWaveServerPage, __FILE__, __LINE__);

    string path             = pWaveServerPage->getPath ();
    bool   isAnExistingPage = isAKnownServerPage (path);

    m_waveServerPageDirectoryRoot.addSibling (path, pWaveServerPage);

    if (true == isAnExistingPage)
    {
        trace (TRACE_LEVEL_FATAL, "WaveServerPageDirectory::registerServerPage : A Page with the path \"" + path + "\" has already been registered.");

        prismAssert (false, __FILE__, __LINE__);
    }
    else
    {
        if (NULL != pWaveServerPage)
        {
            trace (TRACE_LEVEL_DEVEL, "WaveServerPageDirectory::registerServerPage : Registering a Wave Server Page : \"" + path + "\"");

            m_serverPageMap[path] = pWaveServerPage;
        }
    }
}

void WaveServerPageDirectory::registerServerPage (const string &path, WaveServerPage *pWaveServerPage)
{
    bool isAnExistingPage = isAKnownServerPage (path);

    m_waveServerPageDirectoryRoot.addSibling (path, pWaveServerPage);

    if (true == isAnExistingPage)
    {
        trace (TRACE_LEVEL_FATAL, "WaveServerPageDirectory::registerServerPage : A Page with the path \"" + path + "\" has already been registered.");

        prismAssert (false, __FILE__, __LINE__);
    }
    else
    {
        if (NULL != pWaveServerPage)
        {
            trace (TRACE_LEVEL_DEVEL, "WaveServerPageDirectory::registerServerPage : Registering a Wave Server Page : \"" + path + "\"");

            m_serverPageMap[path] = pWaveServerPage;
        }
    }
}

WaveServerPage *WaveServerPageDirectory::getWaveServerPage (const string &path)
{
    return (m_waveServerPageDirectoryRoot.getWaveServerPageForRelativePath (path));
}

ResourceId WaveServerPageDirectory::print (UI32 argc, vector<string> argv)
{
    m_waveServerPageDirectoryRoot.print ();

    return (SHELL_OK);
}

}
