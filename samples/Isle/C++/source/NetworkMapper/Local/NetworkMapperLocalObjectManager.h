/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMAPPERLOCALOBJECTMANAGER_H
#define NETWORKMAPPERLOCALOBJECTMANAGER_H

#include <string>

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

using namespace WaveNs;
using namespace std;

namespace IsleNs
{

class NetworkMapperLocalBootCompletionWorker;

class NetworkMapperLocalObjectManager : public WaveLocalObjectManager
{
    private :
        NetworkMapperLocalObjectManager ();

    protected :
    public :
        virtual                                 ~NetworkMapperLocalObjectManager ();

        static  string                           getServiceName                  ();
        static  NetworkMapperLocalObjectManager *getInstance                     ();

        // Now the data members

    private :
        NetworkMapperLocalBootCompletionWorker *m_pNetworkMapperLocalBootCompletionWorker;

    protected :
    public :
};

}

#endif // NETWORKMAPPERLOCALOBJECTMANAGER_H
