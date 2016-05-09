/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef LIGHTPULSEREGISTRATIONREPOSITORY_H
#define LIGHTPULSEREGISTRATIONREPOSITORY_H

#include "Framework/Types/Types.h"

#include <map>
#include <set>

using namespace std;

namespace WaveNs
{

class LightPulseRegistrationRepository
{
    private :
        LightPulseRegistrationRepository ();

    protected :
    public :
                                                ~LightPulseRegistrationRepository           ();

        static LightPulseRegistrationRepository *getInstance                                ();

               void                              addLightPulseRecepientForLightPulseName    (const string &lightPulseName, const WaveServiceId &recepientWaveServiceId);
               void                              removeLightPulseRecepientForLightPulseName (const string &lightPulseName, const WaveServiceId &recepientWaveServiceId);
               set<WaveServiceId>                getLightPulseRecepientsForLightPulseName   (const string &lightPulseName);

        // Now the data members

    private :
        map<string, set<WaveServiceId> > m_lightPulseRecepientsByLightPulseName;

    protected :
    public :
};

}

#endif // LIGHTPULSEREGISTRATIONREPOSITORY_H
