/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESERVERPAGEFORREST_H
#define WAVESERVERPAGEFORREST_H

#include "HttpInterface/WaveServerPage.h"


namespace WaveNs
{

class WaveServerPageForRest : public WaveServerPage
{
    private :
    protected :
        virtual void requestHandlerForGet (const HttpRequest &httpRequest);

    public :
                       WaveServerPageForRest (HttpInterfaceReceiverObjectManager *pHttpInterfaceReceiverObjectManager, const string &path);
        virtual       ~WaveServerPageForRest ();

        virtual void   get                   (const HttpRequest &httpRequest);
        /*virtual void   head                  (const HttpRequest &httpRequest);
        virtual void   post                  (const HttpRequest &httpRequest);
        virtual void   put                   (const HttpRequest &httpRequest);
        virtual void   deleteMethod          (const HttpRequest &httpRequest);
        virtual void   options               (const HttpRequest &httpRequest);
        virtual void   traceX                (const HttpRequest &httpRequest);
        virtual void   connect               (const HttpRequest &httpRequest);*/

    // Now the data members

    private :
    protected :
    public:
};

}

#endif // WAVESERVERPAGEFORREST_H
