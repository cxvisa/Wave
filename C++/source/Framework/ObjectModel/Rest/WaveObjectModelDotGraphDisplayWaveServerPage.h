/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMODELDOTGRAPHDISPLAYWAVESERVERPAGE_H
#define WAVEOBJECTMODELDOTGRAPHDISPLAYWAVESERVERPAGE_H

#include "HttpInterface/WaveServerPageForRest.h"

namespace WaveNs
{

class WaveObjectModelDotGraphDisplayWaveServerPage : public WaveServerPageForRest
{
    private :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

                void serveFile            (const HttpRequest &httpRequest, const string &filePath);
    protected :
    public :
                 WaveObjectModelDotGraphDisplayWaveServerPage ();
        virtual ~WaveObjectModelDotGraphDisplayWaveServerPage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVEOBJECTMODELDOTGRAPHDISPLAYWAVESERVERPAGE_H
