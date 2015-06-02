/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#include "Framework/Utils/TraceUtils.h"
#include "Framework/CliBlockManagement/CliBlockDetail.h"
#include "Framework/CliBlockManagement/CliBlockContext.h"
#include "Framework/CliBlockManagement/CliBlockServiceIndependentMessage.h"
#include "Framework/CliBlockManagement/CliBlockType.h"

namespace WaveNs
{

CliBlockDetail::CliBlockDetail ()
{
    m_prismServiceId    = 0; 
    m_originator        = 0;
    m_cliBlockContext   = CliBlockContext ();
}

CliBlockDetail::CliBlockDetail (PrismServiceId prismServiceId, LocationId originator, const CliBlockContext &cliBlockContext)
{
    m_prismServiceId    = prismServiceId;
    m_originator        = originator;
    m_cliBlockContext   = cliBlockContext;
}

CliBlockDetail::CliBlockDetail (const CliBlockServiceIndependentMessage &cliBlockServiceIndependentMessage)
{
    m_prismServiceId          = cliBlockServiceIndependentMessage.getPrismServiceId ();
    m_originator              = cliBlockServiceIndependentMessage.getOriginator ();
    m_cliBlockContext         = CliBlockContext (cliBlockServiceIndependentMessage.getReason ());
}

CliBlockDetail::CliBlockDetail (const CliBlockDetail &detail) :
     m_prismServiceId (detail.m_prismServiceId), m_originator (detail.m_originator), m_cliBlockContext (detail.m_cliBlockContext)
{
}

CliBlockDetail::~CliBlockDetail ()
{
}

CliBlockDetail& CliBlockDetail::operator= (const CliBlockDetail &rhs)
{

    if (this == &rhs)
    {
        return (*this); 
    }
    
    m_prismServiceId    = rhs.m_prismServiceId;
    m_originator        = rhs.m_originator; 
    m_cliBlockContext   = rhs.m_cliBlockContext;

    return (*this);
}

const PrismServiceId CliBlockDetail::getPrismServiceId () const
{
    return m_prismServiceId;
}

const LocationId CliBlockDetail::getOriginator () const
{
    return m_originator;
}

const CliBlockContext& CliBlockDetail::getCliBlockContext () const
{
    return m_cliBlockContext;
}

}
