/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDELEMENT_H
#define PFRTHRESHOLDELEMENT_H

#include "xercesc/dom/DOM.hpp"

#include <string>
#include <map>

using namespace std;
using namespace XERCES_CPP_NAMESPACE;

namespace WaveNs
{

class Attribute;

class PfrThresholdElement
{
    private :
    protected :
    public :
                                      PfrThresholdElement                    ();
        virtual                      ~PfrThresholdElement                    ();

        virtual  void                 loadFromDomElement                     (DOMElement *pDomElement);
        virtual  void                 loadTextAttributeFromDomElement        (const string &textAttributeName, DOMElement *pDomElement);
        virtual  PfrThresholdElement *getPfrThresholdElementByName           (const string &pfrThresholdElementName);
        virtual  Attribute           *getTextAttributeByName                 (const string &textAttributeName);

                 string               getNodeName                            () const;
                 void                 setNodeName                            (const string &nodeName);

                 bool                 isAKnownTextAttribute                  (const string &textAttributeName) const;
                 Attribute           *getTextAttribute                       (const string &textAttributeName) const;
                 void                 addTextAttribute                       (const string &textAttributeName, Attribute *pAttribute);

                 bool                 isAKnownPfrThresholdElement            (const string &pfrThresholdElementName) const;
                 PfrThresholdElement *getPfrThresholdElement                 (const string &pfrThresholdElementName) const;
                 void                 addPfrThresholdElement                 (const string &pfrThresholdElementName, PfrThresholdElement *pPfrThresholdElement);

    // Now the data members

    private :
        string                             m_nodeName;
        map<string, Attribute *>           m_nodeTextAttributes;
        map<string, PfrThresholdElement *> m_nodePfrThresholdElements;

    protected :
    public :
};

}

#endif // PFRTHRESHOLDELEMENT_H

