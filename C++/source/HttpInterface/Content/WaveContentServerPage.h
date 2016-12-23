/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECONTENTSERVERPAGE_H
#define WAVECONTENTSERVERPAGE_H

#include "HttpInterface/WaveServerPage.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class WaveContentServerPage : public WaveServerPage
{
    private :
        virtual void get (const HttpRequest &httpReuest);

    protected :
    public :
                 WaveContentServerPage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path);
        virtual ~WaveContentServerPage ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVECONTENTSERVERPAGE_H
