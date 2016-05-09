/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Messaging/LightHouse/LightPulseRegistrationRepository.h"
#include "Framework/Utils/AssertUtils.h"

namespace WaveNs
{

LightPulseRegistrationRepository::LightPulseRegistrationRepository ()
{
}

LightPulseRegistrationRepository::~LightPulseRegistrationRepository ()
{
}

LightPulseRegistrationRepository *LightPulseRegistrationRepository::getInstance ()
{
    static LightPulseRegistrationRepository *pLightPulseRegistrationRepository = new LightPulseRegistrationRepository ();

    WaveNs::waveAssert (NULL != pLightPulseRegistrationRepository, __FILE__, __LINE__);

    return (pLightPulseRegistrationRepository);
}

void LightPulseRegistrationRepository::addLightPulseRecepientForLightPulseName (const string &lightPulseName, const WaveServiceId &recepientWaveServiceId)
{
    (m_lightPulseRecepientsByLightPulseName[lightPulseName]).insert (recepientWaveServiceId);
}

void LightPulseRegistrationRepository::removeLightPulseRecepientForLightPulseName (const string &lightPulseName, const WaveServiceId &recepientWaveServiceId)
{
    map<string, set<WaveServiceId> >::iterator element    = m_lightPulseRecepientsByLightPulseName.find (lightPulseName);
    map<string, set<WaveServiceId> >::iterator endElement = m_lightPulseRecepientsByLightPulseName.end  ();

    if (endElement != element)
    {
        set<WaveServiceId> &recepientWaveServiceIdsForLightPulseName = m_lightPulseRecepientsByLightPulseName[lightPulseName];

        recepientWaveServiceIdsForLightPulseName.erase (recepientWaveServiceIdsForLightPulseName.find (recepientWaveServiceId));
    }
}

set<WaveServiceId> LightPulseRegistrationRepository::getLightPulseRecepientsForLightPulseName (const string &lightPulseName)
{
    map<string, set<WaveServiceId> >::iterator element    = m_lightPulseRecepientsByLightPulseName.find (lightPulseName);
    map<string, set<WaveServiceId> >::iterator endElement = m_lightPulseRecepientsByLightPulseName.end  ();

    if (endElement != element)
    {
        set<WaveServiceId> &recepientWaveServiceIdsForLightPulseName = m_lightPulseRecepientsByLightPulseName[lightPulseName];

        return (recepientWaveServiceIdsForLightPulseName);
    }
    else
    {
        return (set<WaveServiceId> ());
    }
}

}
