/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMLOCALOBJECTMANAGERFORUSERSPECIFICTASKS_H
#define PRISMLOCALOBJECTMANAGERFORUSERSPECIFICTASKS_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class WaveLocalObjectManagerForUserSpecificTasks : public WaveLocalObjectManager
{
    private :
        static void addToUserspecificServicesMap (const WaveServiceId &waveServiceId);

    protected :
        WaveLocalObjectManagerForUserSpecificTasks (const string &objectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);

    public :
        virtual      ~WaveLocalObjectManagerForUserSpecificTasks ();
        static  bool  isAUserSpecificService                      (const WaveServiceId &waveServiceId);

    // now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMLOCALOBJECTMANAGERFORUSERSPECIFICTASKS_H
