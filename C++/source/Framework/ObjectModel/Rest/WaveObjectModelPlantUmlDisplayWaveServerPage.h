/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMODELPLANTUMLDISPLAYWAVESERVERPAGE_H
#define WAVEOBJECTMODELPLANTUMLDISPLAYWAVESERVERPAGE_H

#include "HttpInterface/WaveServerPageForRest.h"

namespace WaveNs
{

class WaveObjectModelPlantUmlDisplayWaveServerPage : public WaveServerPageForRest
{
    private :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

                void serveFile            (const HttpRequest &httpRequest, const string &filePath);
    protected :
    public :
                 WaveObjectModelPlantUmlDisplayWaveServerPage ();
        virtual ~WaveObjectModelPlantUmlDisplayWaveServerPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEOBJECTMODELPLANTUMLDISPLAYWAVESERVERPAGE_H
