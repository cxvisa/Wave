/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Framework/CliBlockManagement/CliBlockContext.h"
#include "Framework/CliBlockManagement/CliBlockType.h"

namespace WaveNs
{

CliBlockContext::CliBlockContext ()
{
    m_reason = WAVE_FRAMEWORK_STATE_UNKNOWN_STATE;
}

CliBlockContext::CliBlockContext (ResourceId reason)
{
    m_reason = reason;
}

CliBlockContext::CliBlockContext (const CliBlockContext &context)
{
    m_reason = context.m_reason;
}

CliBlockContext::~CliBlockContext ()
{
}

CliBlockContext& CliBlockContext::operator= (const CliBlockContext &rhs)
{

    if (this == &rhs)
    {
        return (*this); 
    }
    
    m_reason   = rhs.m_reason;

    return (*this);
}

const ResourceId CliBlockContext::getReason () const
{
    return m_reason;
}

void CliBlockContext::setReason (ResourceId reason)
{
    m_reason = reason;
}

}
