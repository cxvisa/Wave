/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMODELPLANTUMLWAVESERVERPAGE_H
#define WAVEOBJECTMODELPLANTUMLWAVESERVERPAGE_H

#include "HttpInterface/WaveServerPageForRest.h"

namespace WaveNs
{

class WaveObjectModelPlantUmlWaveServerPage : public WaveServerPageForRest
{
    private :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

    protected :
    public :
                 WaveObjectModelPlantUmlWaveServerPage ();
        virtual ~WaveObjectModelPlantUmlWaveServerPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEOBJECTMODELPLANTUMLWAVESERVERPAGE_H
