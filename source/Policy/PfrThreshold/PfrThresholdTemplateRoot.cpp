/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThreshold/PfrThresholdTemplateRoot.h"
#include "Framework/Utils/AssertUtils.h"

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

PfrThresholdTemplateRoot::PfrThresholdTemplateRoot ()
    : PfrThresholdElement ()
{
}

PfrThresholdTemplateRoot::~PfrThresholdTemplateRoot ()
{
}

PfrThresholdElement *PfrThresholdTemplateRoot::getPfrThresholdElementByName (const string &pfrThresholdElementName)
{
    if ("PfrThresholdTemplateElement" == pfrThresholdElementName)
    {
        PfrThresholdTemplateElement *pPfrThresholdTemplateElement = new PfrThresholdTemplateElement ();

        prismAssert (NULL != pPfrThresholdTemplateElement, __FILE__, __LINE__);

        m_pfrThresholdTemplateElements.push_back (pPfrThresholdTemplateElement);

        return (pPfrThresholdTemplateElement);
    }
    else
    {
        return (PfrThresholdElement::getPfrThresholdElementByName (pfrThresholdElementName));
    }
}

void PfrThresholdTemplateRoot::load (const string &pfrThresholdsFileName)
{
    XMLPlatformUtils::Initialize ();

    XercesDOMParser    pfrThresholdsFileParser;
    XMLCh             *pPfrThresholdsFileName   = XMLString::transcode (pfrThresholdsFileName.c_str ());

    pfrThresholdsFileParser.setValidationScheme           (XercesDOMParser::Val_Auto);
    pfrThresholdsFileParser.setDoNamespaces               (false);
    pfrThresholdsFileParser.setDoSchema                   (false);
    pfrThresholdsFileParser.setCreateEntityReferenceNodes (false);

    LocalFileInputSource pfrThresholdsfileInputSource (pPfrThresholdsFileName);

    pfrThresholdsFileParser.parse (pfrThresholdsfileInputSource);

    DOMDocument *pDocument  = pfrThresholdsFileParser.getDocument ();

    if (NULL == pDocument)
    {
        return;
    }

    DOMElement *pDomElement = pDocument->getDocumentElement ();

    if (NULL != pDomElement)
    {
        loadFromDomElement (pDomElement);
    }

    XMLString::release (&pPfrThresholdsFileName);

    //XMLPlatformUtils::Terminate ();
}

vector<PfrThresholdTemplateElement *> &PfrThresholdTemplateRoot::getPfrThresholdTemplateElements ()
{
    return (m_pfrThresholdTemplateElements);
}

}
