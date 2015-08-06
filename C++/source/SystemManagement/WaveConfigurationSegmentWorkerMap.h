/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVECONFIGURATIONSEGMENTWORKERMAP_H
#define WAVECONFIGURATIONSEGMENTWORKERMAP_H

#include "Framework/Utils/WaveMutex.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{
class WaveConfigurationSegmentWorker;

class WaveConfigurationSegmentWorkerMap
{
    private :
    protected :
    public :
        static void     addConfigurationSegmentWorkerIntoMap  (const string &configurationSegmentName, WaveConfigurationSegmentWorker *pWaveConfigurationSegmentWorker);

        static bool     isConfigurationSegmentNameInMap (const string &configurationSegmentName);

    // Now the data members

    private :
        static WaveMutex                                       m_configurationSegmentWorkerMapMutex; 


    protected :
    public :
        static map<string, WaveConfigurationSegmentWorker *>    m_configurationSegmentWorkerMap; // Map from Config Segment Name to Config Segment Worker registered
};

}

#endif // WAVECONFIGURATIONSEGMENTMAP_H
