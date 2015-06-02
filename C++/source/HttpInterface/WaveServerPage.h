/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESERVERPAGE_H
#define WAVESERVERPAGE_H
#include <Framework/Attributes/Attribute.h>
#include "HttpRequest.h"
#include <Framework/ObjectModel/WaveWorker.h>

namespace WaveNs
{

class HttpInterfaceReceiverObjectManager;

class WaveServerPage : public WaveWorker
{

    private :
    protected :
                void setPageHeading            (const string &pageHeading);
        virtual void getListOfOptionsForGet    (vector<string> &optionsForGet) const;
        virtual void getListOfOptionsForPost   (vector<string> &optionsForPost) const;
        virtual void getListOfOptionsForPut    (vector<string> &optionsForPost) const;
        virtual void getListOfOptionsForDelete (vector<string> &optionsForDelete) const;

        virtual void requestHandlerForGet      (const HttpRequest &httpRequest);

    public :
                       WaveServerPage                        (HttpInterfaceReceiverObjectManager *pHttpInterfaceReceiverObjectManager, const string &path);
        virtual       ~WaveServerPage                        ();

        virtual void   get                                   (const HttpRequest &httpRequest);
        virtual void   head                                  (const HttpRequest &httpRequest);
        virtual void   post                                  (const HttpRequest &httpRequest);
        virtual void   put                                   (const HttpRequest &httpRequest);
        virtual void   deleteMethod                          (const HttpRequest &httpRequest);
        virtual void   options                               (const HttpRequest &httpRequest);
        virtual void   traceX                                (const HttpRequest &httpRequest);
        virtual void   connect                               (const HttpRequest &httpRequest);

                string getPageHeading                        () const;

                void   getWaveServerPagePrePortionForGet     (string &waveServerPagePrePortionForGet);
                void   getWaveServerPagePostPortionForGet    (string &waveServerPagePostPortionForGet);

                void   getWaveServerPagePrePortionForPost    (string &waveServerPagePrePortionForPost);
                void   getWaveServerPagePostPortionForPost   (string &waveServerPagePostPortionForPost);

                void   getWaveServerPagePrePortionForPut     (string &waveServerPagePrePortionForPost);
                void   getWaveServerPagePostPortionForPut    (string &waveServerPagePostPortionForPost);

                void   getWaveServerPagePrePortionForDelete  (string &waveServerPagePrePortionForDelete);
                void   getWaveServerPagePostPortionForDelete (string &waveServerPagePostPortionForDelete);

                string getPath                               () const;


    // Now the data members

    private :
        string m_path;
        string m_pageHeading;

    protected :
    public :
};

}

#endif // WAVESERVERPAGE_H

