/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Regression/RegressionTestEntry.h"

namespace WaveNs
{
RegressionTestEntry::RegressionTestEntry ()
    : m_testServiceId (0),
      m_isTestEnabled (false)
{
}

RegressionTestEntry::RegressionTestEntry (WaveServiceId id, bool enabled)
    : m_testServiceId (id),
      m_isTestEnabled (enabled)
{
}

RegressionTestEntry::~RegressionTestEntry ()
{
}

WaveServiceId RegressionTestEntry::getTestServiceId () const
{
    return (m_testServiceId);
}

bool RegressionTestEntry::getIsTestEnabled () const
{
    return (m_isTestEnabled);
}

void RegressionTestEntry::setIsTestEnabled (bool enabled)
{
    m_isTestEnabled = enabled;
}

}
