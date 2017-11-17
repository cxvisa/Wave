/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMODELLOCALOBJECTMANAGER_H
#define NETWORKMODELLOCALOBJECTMANAGER_H

#include <string>

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

using namespace WaveNs;
using namespace std;

namespace IsleNs
{


class NetworkModelLocalBootCompletionWorker;

class NetworkModelLocalObjectManager : public WaveLocalObjectManager
{
    private :
        NetworkModelLocalObjectManager ();

    protected :
    public :
        virtual                                ~NetworkModelLocalObjectManager ();

        static  string                          getServiceName                 ();
        static  NetworkModelLocalObjectManager *getInstance                    ();

        // Now the data members

    private :
        NetworkModelLocalBootCompletionWorker *m_pNetworkModelLocalBootCompletionWorker;

    protected :
    public :
};

}

#endif // NETWORKMODELLOCALOBJECTMANAGER_H
