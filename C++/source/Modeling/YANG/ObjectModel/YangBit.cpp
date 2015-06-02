/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangBit.h"
#include "Modeling/YANG/ObjectModel/YangPosition.h"
#include "Framework/Utils/StringUtils.h"
#include "Modeling/YANG/ObjectModel/YangModule.h"

namespace WaveNs
{

YangBit::YangBit ()
    : YangElement (getYangName (), ""),
      m_position  (0)
{
}

YangBit::~YangBit()
{
}

string YangBit::getYangName ()
{
    return ("bit");
}

YangElement *YangBit::createInstance ()
{
    return (new YangBit ());
}

void YangBit::processChildElement (YangElement *pYangElement)
{
    YangElement::processChildElement (pYangElement);

    const string yangName = pYangElement->getYangName ();

    if ((YangPosition::getYangName()) == yangName)
    {
        YangPosition *pYangPosition = dynamic_cast<YangPosition *> (pYangElement);

        prismAssert (NULL != pYangPosition, __FILE__, __LINE__);

        m_position = pYangPosition->getValue ();
    }
}


void YangBit::getNameForHFileForCLanguage (string &actualName, string &processedNameForCLanguage, string &cLanguageValue) const
{
    string nameForHFileForCLanguage = getVariableNameInProgrammingLanguage ();

    YangModule  *pOwnerYangModule   = getPOwnerYangModule ();
    YangElement *pParentYangElement = getPParentElement   ();

    prismAssert (NULL != pOwnerYangModule,   __FILE__, __LINE__);
    prismAssert (NULL != pParentYangElement, __FILE__, __LINE__);

    if (NULL != pOwnerYangModule)
    {
        string       modulePrefix              = pOwnerYangModule->getPrefix           ();
        YangElement *pParentsParentYangElement = pParentYangElement->getPParentElement ();

        prismAssert (NULL != pParentsParentYangElement, __FILE__, __LINE__);

        string nameForOwnersOwner = pParentsParentYangElement->getName ();

        if (("" != modulePrefix) && ("" != nameForHFileForCLanguage))
        {
            nameForHFileForCLanguage = modulePrefix + "__bm_" + nameForOwnersOwner + "_" + nameForHFileForCLanguage;
        }
    }

    StringUtils::replaceAllInstancesOfInputCharWith (nameForHFileForCLanguage, '-', '_');
    StringUtils::replaceAllInstancesOfInputStringWith (nameForHFileForCLanguage, "/", "0x2f");
    StringUtils::replaceAllInstancesOfInputStringWith (nameForHFileForCLanguage, "+", "0x2b");
    StringUtils::replaceAllInstancesOfInputStringWith (nameForHFileForCLanguage, ".", "0x2e");

    processedNameForCLanguage = nameForHFileForCLanguage;
    cLanguageValue            = string ("(1 << ") + m_position + string (")");

    // Special treatment for Bit elements so that these names do not collide with other namesin global space.

    actualName = processedNameForCLanguage;

    return;
}

bool YangBit::considerForHFileForCLanguage () const
{
    return (true);
}

}
