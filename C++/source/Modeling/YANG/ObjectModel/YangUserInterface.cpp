/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka / Mandar Datar                     *
 ***************************************************************************/

#include "Modeling/YANG/ObjectModel/YangUserInterface.h"
#include "Framework/Utils/AssertUtils.h"
#include "SystemManagement/WaveConfigurationSegmentMap.h"

#include <list>
#include <algorithm>

namespace WaveNs
{

YangUserInterface::YangUserInterface ()
    : YangElement (getYangName (), "")
{
    m_hierarchyInformationForYangElementsInTreeForDataPrepared = false;
}

YangUserInterface::~YangUserInterface()
{
}

string YangUserInterface::getYangName ()
{
    return ("user-interface");
}

YangElement *YangUserInterface::createInstance ()
{
    return (new YangUserInterface ());
}

void YangUserInterface::initializeFromYangModuleCollection (const YangModuleCollection &yangModuleCollection)
{
}

void YangUserInterface::computeCliTargetNodeNameMapForData ()
{
    YangElement::computeCliTargetNodeNameMapForData (m_cliTargetNodeNameMapForData, m_cliTargetNodeNameMapForDataWithDropNodeName);
}

vector<YangElement *> YangUserInterface::getYangElementsByTargetNodeNameForDropNode (const string &targetNodeNameForDropNode)
{
    map<string, vector<YangElement *> >::iterator element    = m_cliTargetNodeNameMapForDataWithDropNodeName.find (targetNodeNameForDropNode);
    map<string, vector<YangElement *> >::iterator endElement = m_cliTargetNodeNameMapForDataWithDropNodeName.end  ();

    if (endElement != element)
    {
        return (element->second);
    }
    else
    {
    	return (vector<YangElement *> ());
    }
}

vector<YangElement *> YangUserInterface::getYangElementsByTargetNodeName (const string &targetNodeName)
{
    map<string, vector<YangElement *> >::iterator element    = m_cliTargetNodeNameMapForData.find (targetNodeName);
    map<string, vector<YangElement *> >::iterator endElement = m_cliTargetNodeNameMapForData.end  ();

    if (endElement != element)
    {
        return (element->second);
    }
    else
    {
        return (vector<YangElement *> ());
    }
}

void YangUserInterface::prepareYangElementTreeForData ()
{
    vector<YangElement *>  &pChildYangElements    = getChildElements ();
    UI32                    numberOfChildElements = pChildYangElements.size ();

    vector<YangModule *>    pChildYangModules;

    for (UI32 i = 0; i < numberOfChildElements; i++)
    {
        YangElement *pChildYangElement = pChildYangElements[i];
        waveAssert (NULL != pChildYangElement, __FILE__, __LINE__);

        YangModule *pYangModule = dynamic_cast<YangModule *> (pChildYangElement);

        if (NULL != pYangModule)
        {
            pChildYangModules.push_back (pYangModule);
        }
        else
        {
            waveAssert (false, __FILE__, __LINE__);    // Rolling reboot case.
        }
    }

    std::stable_sort (pChildYangModules.begin (), pChildYangModules.end (), YangModule::compareYangModulesByNamespaceUri);

    UI32 numberOfChildYangModules = pChildYangModules.size ();

    for (UI32 i = 0; i < numberOfChildYangModules; i++)
    {
        YangModule *pYangModule = pChildYangModules[i];
        waveAssert (NULL != pYangModule, __FILE__, __LINE__);

        vector<YangElement *>  &pChildElementsOfYangModule          = pYangModule->getChildElements ();
        UI32                    numberOfchildElementsOfYangModule   = pChildElementsOfYangModule.size ();

        for (UI32 j = 0; j < numberOfchildElementsOfYangModule; j++)
        {
            YangElement *pYangElement = pChildElementsOfYangModule[j];
            waveAssert (NULL != pYangElement, __FILE__, __LINE__);

            if (true == pYangElement->isYangElementForData ())
            {
                m_moduleChildElementsForData.push_back (pYangElement);
            }
        }
    }

    std::stable_sort (m_moduleChildElementsForData.begin (), m_moduleChildElementsForData.end (), YangElement::compareYangElementsByDataIndex);

    UI32 numberOfModuleChildElementsForData = m_moduleChildElementsForData.size ();

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->setupYangElementTreeForData  ();
    }
}

void YangUserInterface::debugPrintYangElementTreeForData (const string &outputFilePath) const
{
    FILE *pOutputFile = NULL;

    if (true == outputFilePath.empty ())
    {
        pOutputFile = stdout;
    }
    else
    {
        pOutputFile = fopen (outputFilePath.c_str (), "w");

        if (NULL == pOutputFile)
        {
            string errorString = string ("Failed to open outputFile [") + outputFilePath + string ("] ");
            perror (errorString.c_str ());
            return;
        }
    }

    UI32 numberOfModuleChildElementsForData = m_moduleChildElementsForData.size ();

    UI32 depth = 0;

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->debugPrintChildElementInforamtionForData (pOutputFile, depth);
    }

	fclose (pOutputFile);
}

void YangUserInterface::propagateNodeSpecificAndMultiPartitionInformationInDataElementTree ()
{
    UI32 numberOfModuleChildElementsForData = m_moduleChildElementsForData.size ();

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->propagateNodeSpecificInformation ();
    }

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->propagateMultiPartitionInformation ();
    }
}

void YangUserInterface::prepareHierarchyInformationForYangElementsInTreeForData ()
{
    if (true == m_hierarchyInformationForYangElementsInTreeForDataPrepared)
    {
        return;
    }

    UI32 numberOfModuleChildElementsForData = m_moduleChildElementsForData.size ();

    // Managed Object Hierarchy.

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->prepareHierarchyInformation ();
    }

    // Known names in hierarchy.

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->prepareSetOfKnownDisplayNames ();
    }

    for (UI32 i = 0; i < numberOfModuleChildElementsForData; i++)
    {
        YangElement *pYangElement = m_moduleChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        const set<string> &knownDisplayNamesForChildElement = pYangElement->getKnownDisplayNames ();

        for (set<string>::const_iterator itr = knownDisplayNamesForChildElement.begin (); itr != knownDisplayNamesForChildElement.end (); itr++)
        {
            addYangElementForCliToken (*itr, pYangElement);
        }
    }

    // Mark local config subtree -

    vector<YangElement *> &pChildElements = getChildElements ();

    UI32 numberOfchildren = pChildElements.size ();

    for (UI32 i = 0; i < numberOfchildren; i++)
    {
        YangElement *pChildElement = pChildElements[i];

        waveAssert (NULL != pChildElement, __FILE__, __LINE__);

        pChildElement->computeIsInLocalConfigSubtree ();
    }

    // Get ManagedObjectClassName for node-specific and multi-partition base list.

    WaveConfigurationSegmentMap::cacheManagedObjectClassNameForNodeSpecificList ();
    WaveConfigurationSegmentMap::cacheManagedObjectClassNameForMultiPartitionList ();

    m_hierarchyInformationForYangElementsInTreeForDataPrepared = true;
}

void YangUserInterface::printConfiguration (YangDisplayConfigurationContext *pYangDisplayConfigurationContext)
{
    vector<YangElement *> selectedChildElementsForData;

    if (0 != pYangDisplayConfigurationContext->getNumberOfRemainingTokens ())
    {
        string tokenString = pYangDisplayConfigurationContext->advanceToNextToken ();

        getSelectedChildElementsForData (tokenString, selectedChildElementsForData);

        pYangDisplayConfigurationContext->decrementTokenPosition ();
    }
    else
    {
        selectedChildElementsForData = m_moduleChildElementsForData;
    }

    UI32 numberOfSelectedChildElementsForData = selectedChildElementsForData.size ();

    for (UI32 i = 0; i < numberOfSelectedChildElementsForData; i++)
    {
        YangElement *pYangElement = selectedChildElementsForData[i];
        waveAssert (NULL != pYangElement, __FILE__, __LINE__);

        pYangElement->displayConfiguration1 (pYangDisplayConfigurationContext);
    }
}

YangElement *YangUserInterface::getParentYangModuleForGrandChildYangElementByName (const string &uniqueYangElementName, const string &namespaceString) const
{
    YangElement            *pChildModuleElement   = NULL;

    vector<YangElement *>   pChildYangElements;
    getAllChildrenByYangName (YangModule::getYangName (), pChildYangElements);

    UI32                    numberOfChildElements = pChildYangElements.size ();

    for (UI32 i = 0; i < numberOfChildElements; i++)
    {
        YangElement *pChildYangElement = pChildYangElements[i];
        waveAssert (NULL != pChildYangElement, __FILE__, __LINE__);

        YangModule *pYangModule = dynamic_cast<YangModule *> (pChildYangElement);

        if (NULL != pYangModule)
        {
            // trace (TRACE_LEVEL_INFO, "YangUserInterface::getParentYangModuleForGrandChildYangElementByName : searching for [" + uniqueYangElementName + "] in [" + pYangModule->getYangName () + ":" + pYangModule->getName () + "]");

            YangElement *pTargetYangElement = pYangModule->getUniqueYangElementByName (uniqueYangElementName);

            if (NULL != pTargetYangElement)
            {
                pChildModuleElement = pYangModule;
                break;
            }
        }
    }

    // tracePrintf (TRACE_LEVEL_INFO, "YangUserInterface::getParentYangModuleForGrandChildYangElementByName : pYangModule is [%p]", pChildModuleElement);

    return pChildModuleElement;
}

void YangUserInterface::applyAddModeAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("AddMode : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setIsCliAddMode (true);
    }
}

void YangUserInterface::applyCompactElemAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("CompactElem : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setCliCompactSyntax ();
    }
}

void YangUserInterface::applyDropElemAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("DropElem : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setDropNodeNameForCli (true);
    }
}

void YangUserInterface::applyMultiValueAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("MultiValue : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setIsCliMultiValue ();
    }
}

void YangUserInterface::applySuppressModeAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("SuppressMode : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setIsCliSuppressMode (true);
    }
}

void YangUserInterface::applyIncompleteCommandAnnotationToTargetNodes (const string &targetNodeName)
{
    vector<YangElement *> pTargetNodeYangElements = getYangElementsByTargetNodeName (targetNodeName);

    UI32 numberOfTargetNodeYangElements = pTargetNodeYangElements.size ();

    trace (TRACE_LEVEL_INFO, string ("IncompleteCommand : [") + targetNodeName + string ("], numberOfTargetNodeYangElements [") + numberOfTargetNodeYangElements + string ("]"));

    for (UI32 i = 0; i < numberOfTargetNodeYangElements; i++)
    {
        pTargetNodeYangElements[i]->setCliIncompleteCommand (true);
    }
}

void YangUserInterface::applyAnnotationSupplement ()
{
    applyAddModeAnnotation ();
    applyCompactElemAnnotation ();
    applyDropElemAnnotation ();
    applyMultiValueAnnotation ();
    applySuppressModeAnnotation ();
    applyIncompleteCommandAnnotation ();
}

void YangUserInterface::applyAddModeAnnotation ()
{
}

void YangUserInterface::applyCompactElemAnnotation ()
{
}

void YangUserInterface::applyDropElemAnnotation ()
{
}

void YangUserInterface::applyMultiValueAnnotation ()
{
}

void YangUserInterface::applySuppressModeAnnotation ()
{
}

void YangUserInterface::applyIncompleteCommandAnnotation ()
{
}

void YangUserInterface::lock ()
{
    m_mutexToBlockVisibilityInConcurrentReadThreads.lock ();
}

void YangUserInterface::unlock ()
{
    m_mutexToBlockVisibilityInConcurrentReadThreads.unlock ();
}

}
