/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PRISMLOCALOBJECTMANAGER_H
#define PRISMLOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class WaveLocalObjectManager : public WaveObjectManager
{
    private :
    protected :
                     WaveLocalObjectManager (const string &objectManagerName, const UI32 &stackSize = 0, const vector<UI32> *pCpuAffinityVector = NULL);
        virtual bool isALocalPrismService    ();

    public :
        virtual      ~WaveLocalObjectManager ();
        static  bool  isALocalService         (const PrismServiceId &prismServiceId);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PRISMLOCALOBJECTMANAGER_H
