/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef RESERVEDWAVELOCALOBJECTMANAGER_H
#define RESERVEDWAVELOCALOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class ReservedWaveLocalObjectManager : public WaveLocalObjectManager
{
    private :
                 ReservedWaveLocalObjectManager ();
    protected :
    public :
        virtual                                ~ReservedWaveLocalObjectManager ();

        static  ReservedWaveLocalObjectManager *getInstance                    ();
        static  WaveServiceId                  getWaveServiceId              ();
        static  string                          getWaveServiceName            ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // RESERVEDWAVELOCALOBJECTMANAGER_H
