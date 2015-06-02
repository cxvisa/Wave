/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Policy/PfrThreshold/PfrThresholdTemplateElement.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

PfrThresholdTemplateElement::PfrThresholdTemplateElement ()
    : PfrThresholdElement   (),
      m_lossRate            (0),
      m_oneWayDelay         (0),
      m_jitter              (0),
      m_lossRatePriority    (0),
      m_oneWayDelayPriority (0),
      m_jitterPriority      (0)
{
    addPfrThresholdElement("SubCategoryCollection", &m_subCateforyCollection);

    addTextAttribute ("Name",                new AttributeString (&m_templateName));
    addTextAttribute ("LossRate",            new AttributeSI32   (&m_lossRate));
    addTextAttribute ("OneWayDelay",         new AttributeSI32   (&m_oneWayDelay));
    addTextAttribute ("Jitter",              new AttributeSI32   (&m_jitter));
    addTextAttribute ("LossRatePriority",    new AttributeSI32   (&m_lossRatePriority));
    addTextAttribute ("OneWayDelayPriority", new AttributeSI32   (&m_oneWayDelayPriority));
    addTextAttribute ("JitterPriority",      new AttributeSI32   (&m_jitterPriority));
}

PfrThresholdTemplateElement::~PfrThresholdTemplateElement ()
{
}

string PfrThresholdTemplateElement::getTemplateName () const
{
    return (m_templateName);
}

SI32 PfrThresholdTemplateElement::getLossRate () const
{
    return (m_lossRate);
}

SI32 PfrThresholdTemplateElement::getOneWayDelay () const
{
    return (m_oneWayDelay);
}

SI32 PfrThresholdTemplateElement::getJitter () const
{
    return (m_jitter);
}

SI32 PfrThresholdTemplateElement::getLossRatePriority () const
{
    return (m_lossRatePriority);
}

SI32 PfrThresholdTemplateElement::getOneWayDelayPriority () const
{
    return (m_oneWayDelayPriority);
}

SI32 PfrThresholdTemplateElement::getJitterPriority () const
{
    return (m_jitterPriority);
}

PfrThresholdTemplateElementSubCategoryCollection &PfrThresholdTemplateElement::getSubCategoryCollection ()
{
    return (m_subCateforyCollection);
}

}
