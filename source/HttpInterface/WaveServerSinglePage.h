/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESERVERSINGLEPAGE_H
#define WAVESERVERSINGLEPAGE_H

#include "WaveServerPage.h"

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class WaveServerSinglePage : public WaveServerPage
{
    private :
    protected :
    public :
             WaveServerSinglePage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path);
    virtual ~WaveServerSinglePage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESERVERSINGLEPAGE_H
