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
    m_waveServiceId    = 0; 
    m_originator        = 0;
    m_cliBlockContext   = CliBlockContext ();
}

CliBlockDetail::CliBlockDetail (WaveServiceId waveServiceId, LocationId originator, const CliBlockContext &cliBlockContext)
{
    m_waveServiceId    = waveServiceId;
    m_originator        = originator;
    m_cliBlockContext   = cliBlockContext;
}

CliBlockDetail::CliBlockDetail (const CliBlockServiceIndependentMessage &cliBlockServiceIndependentMessage)
{
    m_waveServiceId          = cliBlockServiceIndependentMessage.getWaveServiceId ();
    m_originator              = cliBlockServiceIndependentMessage.getOriginator ();
    m_cliBlockContext         = CliBlockContext (cliBlockServiceIndependentMessage.getReason ());
}

CliBlockDetail::CliBlockDetail (const CliBlockDetail &detail) :
     m_waveServiceId (detail.m_waveServiceId), m_originator (detail.m_originator), m_cliBlockContext (detail.m_cliBlockContext)
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
    
    m_waveServiceId    = rhs.m_waveServiceId;
    m_originator        = rhs.m_originator; 
    m_cliBlockContext   = rhs.m_cliBlockContext;

    return (*this);
}

const WaveServiceId CliBlockDetail::getWaveServiceId () const
{
    return m_waveServiceId;
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
