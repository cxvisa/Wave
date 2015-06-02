/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *       
 *   All rights reserved.                                                  *       
 *   Author : Vidyasagara Reddy Guntaka                                    *       
 ***************************************************************************/

#ifndef NBAR2ELEMENT_H
#define NBAR2ELEMENT_H

#include "xercesc/dom/DOM.hpp"

#include <string>
#include <map>

using namespace std;
using namespace XERCES_CPP_NAMESPACE;

namespace WaveNs
{

class Attribute;

class Nbar2Element
{
    private :
    protected :
    public :
                               Nbar2Element                    ();
        virtual               ~Nbar2Element                    ();
  
        virtual  void          loadFromDomElement              (DOMElement *pDomElement);
        virtual  void          loadTextAttributeFromDomElement (const string &textAttributeName, DOMElement *pDomElement);
        virtual  Nbar2Element *getNbar2ElementByName           (const string &nbar2ElementName);
        virtual  Attribute    *getTextAttributeByName          (const string &textAttributeName);

                 string        getNodeName                     () const;
                 void          setNodeName                     (const string &nodeName);

                 bool          isAKnownTextAttribute           (const string &textAttributeName) const;
                 Attribute    *getTextAttribute                (const string &textAttributeName) const;
                 void          addTextAttribute                (const string &textAttributeName, Attribute *pAttribute);
 
                 bool          isAKnownNbar2Element            (const string &nbar2ElementName) const;
                 Nbar2Element *getNbar2Element                 (const string &nbar2ElementName) const;
                 void          addNbar2Element                 (const string &nbar2ElementName, Nbar2Element *pNbar2Element);

    // Now the data members

    private :
        string                      m_nodeName;
        map<string, Attribute *>    m_nodeTextAttributes;
        map<string, Nbar2Element *> m_nodeNbar2Elements;

    protected :
    public :
};

}

#endif // NBAR2ELEMENT_H

