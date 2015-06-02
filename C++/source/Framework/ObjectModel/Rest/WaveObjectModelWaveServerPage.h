/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMODELWAVESERVERPAGE_H
#define WAVEOBJECTMODELWAVESERVERPAGE_H

#include "HttpInterface/WaveServerPageForRest.h"

namespace WaveNs
{

class WaveObjectModelWaveServerPage : public WaveServerPageForRest
{
    private :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

    protected :
    public :
                 WaveObjectModelWaveServerPage ();
        virtual ~WaveObjectModelWaveServerPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEOBJECTMODELWAVESERVERPAGE_H
