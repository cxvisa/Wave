/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVELOCALOBJECTMANAGER_H
#define WAVELOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class WaveLocalObjectManager : public WaveObjectManager
{
    private :
    protected :
                     WaveLocalObjectManager (const string &objectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
        virtual bool isALocalWaveService    ();

    public :
        virtual      ~WaveLocalObjectManager ();
        static  bool  isALocalService         (const WaveServiceId &waveServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVELOCALOBJECTMANAGER_H
