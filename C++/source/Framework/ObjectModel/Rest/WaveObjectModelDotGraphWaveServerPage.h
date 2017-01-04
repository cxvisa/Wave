/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMODELDOTGRAPHWAVESERVERPAGE_H
#define WAVEOBJECTMODELDOTGRAPHWAVESERVERPAGE_H

#include "HttpInterface/WaveServerPageForRest.h"

namespace WaveNs
{

class WaveObjectModelDotGraphWaveServerPage : public WaveServerPageForRest
{
    private :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

    protected :
    public :
                 WaveObjectModelDotGraphWaveServerPage ();
        virtual ~WaveObjectModelDotGraphWaveServerPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEOBJECTMODELDOTGRAPHWAVESERVERPAGE_H
