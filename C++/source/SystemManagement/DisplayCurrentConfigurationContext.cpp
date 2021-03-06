/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "SystemManagement/DisplayCurrentConfigurationContext.h"
#include "Modeling/YANG/ObjectModel/YangDisplayConfigurationContext.h"
#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Framework/ObjectModel/WaveManagedObjectQueryContext.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

DisplayCurrentConfigurationContext::DisplayCurrentConfigurationContext (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps)
    : WaveLinearSequencerContext        (pWaveMessage, pWaveElement, pSteps, numberOfSteps),
      m_pYangDisplayConfigurationContext (NULL),
      m_currentYangElementIndex          (0),
      m_pYangElement                     (NULL),
      m_pWaveManagedObjectQueryContext   (NULL)
{
}

DisplayCurrentConfigurationContext::~DisplayCurrentConfigurationContext ()
{
    if (NULL != m_pYangDisplayConfigurationContext)
    {
        delete m_pYangDisplayConfigurationContext;

        m_pYangDisplayConfigurationContext = NULL;
    }

    if (NULL != m_pWaveManagedObjectQueryContext)
    {
        delete m_pWaveManagedObjectQueryContext;

        m_pWaveManagedObjectQueryContext = NULL;
    }
}

YangDisplayConfigurationContext *DisplayCurrentConfigurationContext::getPYangDisplayConfigurationContext ()
{
    return (m_pYangDisplayConfigurationContext);
}

void DisplayCurrentConfigurationContext::setPYangDisplayConfigurationContext (YangDisplayConfigurationContext *pYangDisplayConfigurationContext)
{
    m_pYangDisplayConfigurationContext = pYangDisplayConfigurationContext;
}

vector<YangElement *> DisplayCurrentConfigurationContext::getYangElements ()
{
    return (m_yangElements);
}

void DisplayCurrentConfigurationContext::setYangElements (vector<YangElement *> &yangElements)
{
    UI32 numberOfYangElements = m_yangElements.size ();

    waveAssert (0 == numberOfYangElements, __FILE__, __LINE__);

    m_yangElements = yangElements;

    m_currentYangElementIndex = 0;

    m_pYangElement = m_yangElements[m_currentYangElementIndex];

    waveAssert (NULL != m_pYangElement, __FILE__, __LINE__);
}

UI32 DisplayCurrentConfigurationContext::getCurrentYangElementIndex () const
{
    return (m_currentYangElementIndex);
}

void DisplayCurrentConfigurationContext::advanceToNextYangElement ()
{
    bool isAtLast = isAtTheLastYangElement ();

    if (true == isAtLast)
    {
        waveAssert (false, __FILE__, __LINE__);
    }
    else
    {
        m_currentYangElementIndex++;

        m_pYangElement = m_yangElements[m_currentYangElementIndex];

        waveAssert (NULL != m_pYangElement, __FILE__, __LINE__);
    }
}

bool DisplayCurrentConfigurationContext::isAtTheLastYangElement ()
{
    UI32 numberOfYangElements = m_yangElements.size ();

    if (0 == numberOfYangElements)
    {
        waveAssert (false, __FILE__, __LINE__);
    }

    if ((numberOfYangElements - 1) == m_currentYangElementIndex)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

YangElement *DisplayCurrentConfigurationContext::getPYangElement ()
{
    return (m_pYangElement);
}

void DisplayCurrentConfigurationContext::setPYangElement (YangElement *pYangElement)
{
    m_pYangElement = pYangElement;
}

WaveManagedObjectQueryContext *DisplayCurrentConfigurationContext::getPWaveManagedObjectQueryContext ()
{
    return (m_pWaveManagedObjectQueryContext);
}

void DisplayCurrentConfigurationContext::setPWaveManagedObjectQueryContext (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext)
{
    if (NULL != m_pWaveManagedObjectQueryContext)
    {
        delete m_pWaveManagedObjectQueryContext;
    }

    m_pWaveManagedObjectQueryContext = pWaveManagedObjectQueryContext;
}

}
