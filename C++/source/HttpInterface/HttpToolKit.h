/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef HTTPTOOLKIT_H
#define HTTPTOOLKIT_H

#include "Framework/Types/Types.h"
#include "Framework/Types/Uri.h"

#include <string>

using namespace std;

namespace WaveNs
{

class HttpToolKit
{
    private :
    protected :
    public :
        static WaveHttpInterfaceMethod getHttpInterfaceMethod             (const string &httpRequest);
        static WaveHttpInterfaceMethod getHttpInterfaceMethodFromString   (const string &httpRequestMethodString);

        static WaveHttpContentType     getHttpContentTypeFromString       (const string &contentTypeString);

        static void                    addHeader                          (string &httpResponseString);
        static void                    addFooter                          (string &httpResponseString);
        static void                    getFrontPage                       (string &frontPageString);
        static void                    getNotImplementedErrorString       (string &notImplementedErrorString);
        static void                    getMethodNotAllowedErrorString     (string &methodNotAllowedErrorString);
        static void                    getNotFoundErrorString             (string &notFoundErrorString);
        static void                    getUnauthorizedString              (string &unAuthorizedString);
        static void                    getBadRequestString                (string &badRequestString, const string &reason = "Bad Request");
        static void                    getCreatedString                   (string &createdString, const string &createdUri);
        static void                    getCreatedStringForRestXml         (string &createdString, const string &createdUri, const string &xmlBody);
        static void                    getDeletedStringForRestXml         (string &deletedString, const string &xmlBody);

        static void                    getOkStringForGetForRestXml        (string &okString, const string &xmlBody);
        static void                    getNoContentStringForPutForRestXml (string &noContentString);

        static void                    getOkStringForGetForRestJson       (string &okString, const string &jsonBody);

        static void                    decodeUrl                          (string &url);

        static void                    getWaveServerPagePrePortion        (string &waveServerPagePrePortion);
        static void                    getWaveServerPagePostPortion       (string &waveServerPagePostPortion);

        static void                    getSimpleJsonPostString            (string &jsonPostString, const string &jsonContent, const Uri &url);

    // Now the data members

    private :
    protected :
    public :
};
}

#endif // HTTPTOOLKIT_H
