/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/FileUtils.h"
#include "HttpInterface/HttpToolKit.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpInterface/Content/WaveContentServerPage.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace WaveNs
{

WaveContentServerPage::WaveContentServerPage(HttpInterfaceReceiverObjectManager *pHttpInterfaceReceiverObjectManager, const string &path)
    : WaveServerPage (pHttpInterfaceReceiverObjectManager, path)
{
}

WaveContentServerPage::~WaveContentServerPage ()
{
}

void WaveContentServerPage::get (const HttpRequest &httpRequest)
{
          ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();
    const string                 path                   = httpRequest.getUri                    ();

          string                 adjustedUri            = path;
          string                 httpResponseString;

    if (0 == (adjustedUri.find ("/content/")))
    {
        adjustedUri.erase (0, 1);

               ifstream inputFileStream (adjustedUri.c_str (), ios::binary | ios::in);
        static UI8      buffer[4096];

        if (inputFileStream.good ())
        {
            inputFileStream.seekg (0, ios::end);

            const UI32 contentSize = inputFileStream.tellg ();

            const string contentType = FileUtils::getMimeTypeForFile (adjustedUri);

            HttpToolKit::getOkStringWithContentTypeAndLength (httpResponseString, contentType, contentSize);

            (*pServerStreamingSocket) << httpResponseString;

            inputFileStream.clear ();
            inputFileStream.seekg (0, ios::beg);

            while (inputFileStream.read ((char *) buffer, 4096))
            {
                int count = inputFileStream.gcount ();

                pServerStreamingSocket->send (buffer, count);
            }

            if (!inputFileStream)
            {
                int count = inputFileStream.gcount ();

                if (0 < count)
                {
                    pServerStreamingSocket->send (buffer, count);
                }
            }
        }
        else
        {
            HttpToolKit::getNotFoundErrorString (httpResponseString);

            (*pServerStreamingSocket) << httpResponseString;
        }
    }
    else
    {
        HttpToolKit::getNotFoundErrorString (httpResponseString);

        (*pServerStreamingSocket) << httpResponseString;
    }
}

}
