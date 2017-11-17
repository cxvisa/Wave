/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMAPPEROBJECTMANAGER_H
#define NETWORKMAPPEROBJECTMANAGER_H

#include <string>

#include "Framework/ObjectModel/WaveObjectManager.h"

using namespace WaveNs;
using namespace std;

namespace IsleNs
{

class NetworkMapperObjectManager : public WaveObjectManager
{
    private :
        NetworkMapperObjectManager ();

    protected :
    public :
        virtual                            ~NetworkMapperObjectManager ();

        static  string                      getServiceName             ();
        static  NetworkMapperObjectManager *getInstance                ();

        // Now the data members

    private :
    protected :
    public :
};

}

#endif // NETWORKMAPPEROBJECTMANAGER_H
