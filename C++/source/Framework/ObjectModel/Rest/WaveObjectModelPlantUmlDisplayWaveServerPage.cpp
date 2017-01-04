/***************************************************************************
 *   Copyright (C) 2005-2017 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "Framework/Utils/ServerStreamingSocket.h"
#include "Framework/ObjectModel/Rest/WaveObjectModelPlantUmlDisplayWaveServerPage.h"
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

WaveObjectModelPlantUmlDisplayWaveServerPage::WaveObjectModelPlantUmlDisplayWaveServerPage ()
    : WaveServerPageForRest (HttpInterfaceReceiverObjectManager::getInstance (), "/Wave/Rest/ObjectModel/plantUml.png")
{
}

WaveObjectModelPlantUmlDisplayWaveServerPage::~WaveObjectModelPlantUmlDisplayWaveServerPage ()
{
}

void WaveObjectModelPlantUmlDisplayWaveServerPage::requestHandlerForGet (const HttpRequest &httpRequest)
{
    set<string> filters;
    string      ormOutput;
    string      okString;

    OrmRepository::getPlantUmlOrm (filters, ormOutput);

    const char *pPlantUmlFilePath    = "/tmp/WavePlantUml.uml";
    const char *pPlantUmlPngFilePath = "/tmp/WavePlantUml.png";

    ofstream plantUmlFile (pPlantUmlFilePath);

    plantUmlFile << ormOutput;

    plantUmlFile.close ();

    vector<string> systemOutput;

    FrameworkToolKit::systemCommandOutput (string ("plantuml -tpng ") + pPlantUmlFilePath, systemOutput);

    serveFile (httpRequest, string (pPlantUmlPngFilePath));

    FrameworkToolKit::systemCommandOutput (string ("rm -rf ") + pPlantUmlFilePath + string ("; rm -rf ") + pPlantUmlPngFilePath + string (";"), systemOutput);
}

void WaveObjectModelPlantUmlDisplayWaveServerPage::serveFile (const HttpRequest &httpRequest, const string &filePath)
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
