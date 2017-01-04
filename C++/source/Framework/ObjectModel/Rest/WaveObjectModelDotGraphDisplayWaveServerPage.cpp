/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/ObjectModel/Rest/WaveObjectModelDotGraphDisplayWaveServerPage.h"
#include "Framework/ObjectModel/WaveManagedObject.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"
#include "HttpInterface/HttpToolKit.h"
#include "Framework/Utils/FrameworkToolKit.h"
#include "Framework/Utils/FileUtils.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
namespace WaveNs
{

WaveObjectModelDotGraphDisplayWaveServerPage::WaveObjectModelDotGraphDisplayWaveServerPage ()
    : WaveServerPageForRest (HttpInterfaceReceiverObjectManager::getInstance (), "/Wave/Rest/ObjectModel/dotGraph.png")
{
}

WaveObjectModelDotGraphDisplayWaveServerPage::~WaveObjectModelDotGraphDisplayWaveServerPage ()
{
}

void WaveObjectModelDotGraphDisplayWaveServerPage::requestHandlerForGet (const HttpRequest &httpRequest)
{
    set<string> filters;
    string      ormOutput;
    string      okString;

    OrmRepository::getDotGraphOrm (filters, ormOutput);

    const char *pDotGraphFilePath    = "/tmp/WaveDotGraph.uml";
    const char *pDotGraphPngFilePath = "/tmp/WaveDotGraph.png";

    ofstream plantUmlFile (pDotGraphFilePath);

    plantUmlFile << ormOutput;

    plantUmlFile.close ();

    vector<string> systemOutput;

    FrameworkToolKit::systemCommandOutput (string ("dot -T png -o ") + pDotGraphPngFilePath + string (" ") + pDotGraphFilePath, systemOutput);

    serveFile (httpRequest, string (pDotGraphPngFilePath));

    FrameworkToolKit::systemCommandOutput (string ("rm -rf ") + pDotGraphFilePath + string ("; rm -rf ") + pDotGraphPngFilePath + string (";"), systemOutput);
}

void WaveObjectModelDotGraphDisplayWaveServerPage::serveFile (const HttpRequest &httpRequest, const string &filePath)
{
          ServerStreamingSocket *pServerStreamingSocket = httpRequest.getPServerStreamingSocket ();
          string                 httpResponseString;


          ifstream inputFileStream (filePath.c_str (), ios::binary | ios::in);
    static UI8     buffer[4096];

    if (inputFileStream.good ())
    {
        inputFileStream.seekg (0, ios::end);

        const UI32 contentSize = inputFileStream.tellg ();

        const string contentType = FileUtils::getMimeTypeForFile (filePath);

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
}
