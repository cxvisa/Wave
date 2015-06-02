/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveClientSessionContext.h"

namespace WaveNs
{

WaveClientSessionContext::WaveClientSessionContext ()
    : m_waveClientOriginatingLocationId (0),
      m_waveNativeClientId              (0),
      m_waveUserClientId                (0)
{
}

WaveClientSessionContext::WaveClientSessionContext (const LocationId &waveClientOriginatingLocationId, const UI32 &waveNativeClientId, const UI32 &waveUserClientId)
    : m_waveClientOriginatingLocationId (waveClientOriginatingLocationId),
      m_waveNativeClientId              (waveNativeClientId),
      m_waveUserClientId                (waveUserClientId)
{
}

WaveClientSessionContext::~WaveClientSessionContext ()
{
}

void WaveClientSessionContext::setWaveClientOriginatingLocationId (const LocationId &waveClientOriginatingLocationId)
{
    m_waveClientOriginatingLocationId = waveClientOriginatingLocationId;
}

LocationId WaveClientSessionContext::getWaveClientOriginatingLocationId () const
{
    return (m_waveClientOriginatingLocationId);
}

void WaveClientSessionContext::setWaveNativeClientId (const UI32 &waveNativeClientId)
{
    m_waveNativeClientId = waveNativeClientId;
}

UI32 WaveClientSessionContext::getWaveNativeClientId () const
{
    return (m_waveNativeClientId);
}

void WaveClientSessionContext::setWaveUserClientId (const UI32 &waveUserClientId)
{
    m_waveUserClientId = waveUserClientId;
}

UI32 WaveClientSessionContext::getWaveUserClientId () const
{
    return (m_waveUserClientId);
}

}
