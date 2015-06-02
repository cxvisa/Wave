/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/NBAR2/Nbar2.h"
#include "Framework/Utils/AssertUtils.h"
#include "Framework/Utils/StringUtils.h"
#include "Framework/Utils/TraceUtils.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <ctype.h>

#include <vector>
#include <algorithm>

using namespace XERCES_CPP_NAMESPACE;
using namespace std;

namespace WaveNs
{

Nbar2::Nbar2 ()
    : Nbar2Element ()
{
    addNbar2Element ("info", &m_info);
}

Nbar2::~Nbar2 ()
{
    UI32 numberOfProtocols = m_protocols.size ();
    UI32 i                 = 0;

    for (i = 0; i < numberOfProtocols; i++)
    {
        delete (m_protocols[i]);
    }
}

void Nbar2::load (const string &nbar2FileName)
{
    XMLPlatformUtils::Initialize ();

    XercesDOMParser    nbar2FileParser;
    XMLCh             *pNbar2FileName      = XMLString::transcode (nbar2FileName.c_str ());

    nbar2FileParser.setValidationScheme           (XercesDOMParser::Val_Auto);
    nbar2FileParser.setDoNamespaces               (false);
    nbar2FileParser.setDoSchema                   (false);
    nbar2FileParser.setCreateEntityReferenceNodes (false);

    LocalFileInputSource nbar2fileInputSource (pNbar2FileName);

    nbar2FileParser.parse (nbar2fileInputSource);

    DOMDocument *pDocument  = nbar2FileParser.getDocument ();

    if (NULL == pDocument)
    {
        return;
    }

    DOMElement *pDomElement = pDocument->getDocumentElement ();

    if (NULL != pDomElement)
    {
        loadFromDomElement (pDomElement);
    }

    XMLString::release (&pNbar2FileName);

    //XMLPlatformUtils::Terminate ();

    computeProtocolByNameMap ();
}

Nbar2Element *Nbar2::getNbar2ElementByName  (const string &nbar2ElementName)
{
    if ("protocol" == nbar2ElementName)
    {
        Nbar2Protocol *pNbar2Protocol = new Nbar2Protocol ();

        prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

        m_protocols.push_back (pNbar2Protocol);

        return (pNbar2Protocol);
    }
    else
    {
        return (Nbar2Element::getNbar2ElementByName (nbar2ElementName));
    }
}

string Nbar2::getAdjustedCategoryName (const string &nbar2CategoryName, const string &nbar2SubCategoryName)
{
    string adjustedCategoryName = nbar2CategoryName;

    if (nbar2SubCategoryName == "consumer-audio-streaming" && nbar2CategoryName == "voice-and-video")
    {
        adjustedCategoryName = "consumer_apps";
    }

    if (nbar2SubCategoryName == "consumer-video-streaming" && nbar2CategoryName == "voice-and-video")
    {
        adjustedCategoryName = "consumer_apps";
    }

    if (nbar2SubCategoryName == "consumer-multimedia-messaging" && nbar2CategoryName == "voice-and-video")
    {
        adjustedCategoryName = "consumer_apps";
    }

    if (nbar2SubCategoryName == "p2p-file-transfer" && nbar2CategoryName == "file-sharing")
    {
        adjustedCategoryName = "consumer_apps";
    }

    if (nbar2SubCategoryName == "consumer-web-browsing")
    {
        if (nbar2CategoryName == "email" || nbar2CategoryName == "browsing")
        {
            adjustedCategoryName = "consumer_apps";
        }
    }

    if (nbar2SubCategoryName == "consumer-cloud-storage" && nbar2CategoryName == "backup-and-storage")
    {
        adjustedCategoryName = "consumer_apps";
    }

    if (nbar2SubCategoryName == "other")
    {
        /*
         * if (nbar2CategoryName == "voice-and-video" ||
         * nbar2CategoryName == "net-admin" ||
         * nbar2CategoryName == "location-based-services" ||
         * nbar2CategoryName == "layer3-over-ip" ||
         * nbar2CategoryName == "inter-process-rpc" ||
         * nbar2CategoryName == "industrial-protocols" ||
         * nbar2CategoryName == "file-sharing" ||
         * nbar2CategoryName == "email" ||
         * nbar2CategoryName == "business-and-productivity-tools" ||
         * nbar2CategoryName == "browsing") ||
         * nbar2CategoryName == "backup-and-storage") { adjustedCategoryName = "other"; }
         */
        adjustedCategoryName = "other";
    }

    if (nbar2SubCategoryName == "control-and-signaling" && nbar2CategoryName == "other")
    {
        adjustedCategoryName = "net-admin";
    }

    if (nbar2SubCategoryName == "enterprise-media-conferencing" && nbar2CategoryName == "instant-messaging")
    {
        adjustedCategoryName = "voice-and-video";
    }

    return adjustedCategoryName;
}

set<string> Nbar2::getAdjustedCategoryNames () const
{
    UI32        numberOfProtocols      = m_protocols.size ();
    UI32        i                      = 0;
    set<string> adjustedCategoryNames;

    trace (TRACE_LEVEL_INFO, string ("Nbar2::getAdjustedCategoryNames : Number Of Protocols : ") + numberOfProtocols);

    for (i = 0; i < numberOfProtocols; i++)
    {
        Nbar2Protocol *pNbar2Protocol = m_protocols[i];

        prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

        const string adjustedCategoryName = pNbar2Protocol->getAdjustedCategoryName ();

        trace (TRACE_LEVEL_INFO, string ("Nbar2::getAdjustedCategoryNames :    Protocol : " + pNbar2Protocol->getName () + ", Adjusted Category : ") + adjustedCategoryName);

        adjustedCategoryNames.insert (adjustedCategoryName);
    }

    return (adjustedCategoryNames);
}

set<string> Nbar2::getAllProtocolNames () const
{
    UI32        numberOfProtocols = m_protocols.size ();
    UI32        i                 = 0;
    set<string> allProtocolNames;

    trace (TRACE_LEVEL_INFO, string ("Nbar2::getAllProtocolNames : Number Of Protocols : ") + numberOfProtocols);

    for (i = 0; i < numberOfProtocols; i++)
    {
        Nbar2Protocol *pNbar2Protocol = m_protocols[i];

        prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

        allProtocolNames.insert (pNbar2Protocol->getName ());
    }

    return (allProtocolNames);
}

void Nbar2::computeProtocolByNameMap ()
{
    UI32        numberOfProtocols      = m_protocols.size ();
    UI32        i                      = 0;
    set<string> adjustedCategoryNames;

    trace (TRACE_LEVEL_INFO, string ("Nbar2::computeProtocolByNameMap : Number Of Protocols : ") + numberOfProtocols);

    for (i = 0; i < numberOfProtocols; i++)
    {
        Nbar2Protocol *pNbar2Protocol = m_protocols[i];

        prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

        addToKnownProtocols (pNbar2Protocol->getName (), pNbar2Protocol);
    }
}

bool Nbar2::isAKnownProtocol (const string &protocolName)
{
    map<string, Nbar2Protocol *>::iterator element    = m_protocolByNameMap.find (protocolName);
    map<string, Nbar2Protocol *>::iterator endElement = m_protocolByNameMap.end  ();

    if (endElement == element)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

void Nbar2::addToKnownProtocols (const string &protocolName, Nbar2Protocol *pNbar2Protocol)
{
    prismAssert (NULL != pNbar2Protocol, __FILE__, __LINE__);

    map<string, Nbar2Protocol *>::iterator element    = m_protocolByNameMap.find (protocolName);
    map<string, Nbar2Protocol *>::iterator endElement = m_protocolByNameMap.end  ();

    if (endElement == element)
    {
        m_protocolByNameMap[protocolName] = pNbar2Protocol;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

Nbar2Protocol *Nbar2::getNbar2Protocol (const string &protocolName)
{
    map<string, Nbar2Protocol *>::iterator element    = m_protocolByNameMap.find (protocolName);
    map<string, Nbar2Protocol *>::iterator endElement = m_protocolByNameMap.end  ();

    if (endElement == element)
    {
        return (NULL);
    }
    else
    {
        return (element->second);
    }
}


}

