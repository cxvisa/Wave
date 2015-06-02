/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVETRACESERVERMULTIPAGE_H
#define WAVETRACESERVERMULTIPAGE_H

#include <HttpInterface/WaveServerMultiPage.h>

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class WaveTraceServerMultiPage : public WaveServerMultiPage
{
    private :

        void getForList (const HttpRequest &httpRequest);

    protected :
    public :
                      WaveTraceServerMultiPage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path);
        virtual      ~WaveTraceServerMultiPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVETRACESERVERMULTIPAGE_H
