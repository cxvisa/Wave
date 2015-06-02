/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PolicyObjectManagerInitializationContext.h"

namespace WaveNs
{

string PolicyObjectManagerInitializationContext::m_nbar2FileName         = "NBAR2_Taxonomy.xml";
string PolicyObjectManagerInitializationContext::m_pfrThresholdsFileName = "PfrThresholdTemplates.xml";

PolicyObjectManagerInitializationContext::PolicyObjectManagerInitializationContext (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismMessage, pPrismElement, pSteps, numberOfSteps)
{
}

PolicyObjectManagerInitializationContext::PolicyObjectManagerInitializationContext (PrismAsynchronousContext *pPrismAsynchronousContext, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : PrismLinearSequencerContext (pPrismAsynchronousContext, pPrismElement, pSteps, numberOfSteps)
{
}

PolicyObjectManagerInitializationContext::~PolicyObjectManagerInitializationContext ()
{
}

Nbar2 &PolicyObjectManagerInitializationContext::getNbar2 ()
{
    return (m_nbar2);
}

set<string> &PolicyObjectManagerInitializationContext::getAdjustedCategoryNames ()
{
    return (m_adjustedCategoryNames);
}

string PolicyObjectManagerInitializationContext::getNbar2FileName () const
{
    return (m_nbar2FileName);
}

void PolicyObjectManagerInitializationContext::loadNbar2 ()
{
    m_nbar2.load (m_nbar2FileName);
}

void PolicyObjectManagerInitializationContext::computeAdjustedCategoryNames ()
{
    m_adjustedCategoryNames = m_nbar2.getAdjustedCategoryNames ();
}

string PolicyObjectManagerInitializationContext::getPfrThresholdsFileName ()
{
    return (m_pfrThresholdsFileName);
}

PfrThresholdTemplateRoot &PolicyObjectManagerInitializationContext::getPfrThresholdTemplateRoot ()
{
    return (m_pfrThresholdTemplateRoot);
}

void PolicyObjectManagerInitializationContext::loadPfrThresholdTemplateRoot ()
{
    m_pfrThresholdTemplateRoot.load (m_pfrThresholdsFileName);
}

void PolicyObjectManagerInitializationContext::addSubCategoryToPfrThresholdMapping (const string &subCategoryName, const ObjectId &pfrThresholdTemplateObjectId)
{
    map<string, ObjectId>::const_iterator element    = m_subCategoryToPfrThresholdMap.find (subCategoryName);
    map<string, ObjectId>::const_iterator endElement = m_subCategoryToPfrThresholdMap.end  ();

    if (endElement == element)
    {
        m_subCategoryToPfrThresholdMap[subCategoryName] = pfrThresholdTemplateObjectId;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

void PolicyObjectManagerInitializationContext::getSubCategoryToPfrThresholdMappings (vector<pair <string, ObjectId> > &subCategoryToPfrThresholdMappings) const
{
    map<string, ObjectId>::const_iterator element    = m_subCategoryToPfrThresholdMap.begin ();
    map<string, ObjectId>::const_iterator endElement = m_subCategoryToPfrThresholdMap.end   ();

    while (endElement != element)
    {
        subCategoryToPfrThresholdMappings.push_back (pair<string, ObjectId> (element->first, element->second));

        element++;
    }
}

void PolicyObjectManagerInitializationContext::addCategoryNameToObjectIdMapping (const string &categoryName, const ObjectId &categoryObjectId)
{
    map<string, ObjectId>::iterator element    = m_categoryNameToObjectIdMap.find (categoryName);
    map<string, ObjectId>::iterator endElement = m_categoryNameToObjectIdMap.end  ();

    if (endElement == element)
    {
        m_categoryNameToObjectIdMap[categoryName] = categoryObjectId;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

ObjectId PolicyObjectManagerInitializationContext::getCategoryObjectId (const string &categoryName)
{
    map<string, ObjectId>::iterator element    = m_categoryNameToObjectIdMap.find (categoryName);
    map<string, ObjectId>::iterator endElement = m_categoryNameToObjectIdMap.end  ();

    if (endElement != element)
    {
        return (m_categoryNameToObjectIdMap[categoryName]);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);

        return (ObjectId::NullObjectId);
    }
}

void PolicyObjectManagerInitializationContext::addSubCategoryNameToObjectIdMapping (const string &subCategoryName, const ObjectId &subCategoryObjectId)
{
    map<string, ObjectId>::iterator element    = m_subCategoryNameToObjectIdMap.find (subCategoryName);
    map<string, ObjectId>::iterator endElement = m_subCategoryNameToObjectIdMap.end  ();

    if (endElement == element)
    {
        m_subCategoryNameToObjectIdMap[subCategoryName] = subCategoryObjectId;
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);
    }
}

ObjectId PolicyObjectManagerInitializationContext::getSubCategoryObjectId (const string &subCategoryName)
{
    map<string, ObjectId>::iterator element    = m_subCategoryNameToObjectIdMap.find (subCategoryName);
    map<string, ObjectId>::iterator endElement = m_subCategoryNameToObjectIdMap.end  ();

    if (endElement != element)
    {
        return (m_subCategoryNameToObjectIdMap[subCategoryName]);
    }
    else
    {
        prismAssert (false, __FILE__, __LINE__);

        return (ObjectId::NullObjectId);
    }
}

}

