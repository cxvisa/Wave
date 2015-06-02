/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEDEBUGSERVERPAGE_H
#define WAVEDEBUGSERVERPAGE_H

#include <HttpInterface/WaveServerPage.h>

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;
class WaveTraceServerMultiPage;

class WaveDebugServerPage : public WaveServerPage
{
    private :
    protected :
    public :
                 WaveDebugServerPage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path);
        virtual ~WaveDebugServerPage ();

    // Now the data members

    private :
        WaveTraceServerMultiPage *m_pWaveTraceServerMultiPage;

    protected :
    public :
};

}

#endif // WAVEDEBUGSERVERPAGE_H
