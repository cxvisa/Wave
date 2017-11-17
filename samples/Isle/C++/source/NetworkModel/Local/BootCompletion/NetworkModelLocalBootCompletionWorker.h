/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NETWORKMODELLOCALBOOTCOMPLETIONWORKER_H
#define NETWORKMODELLOCALBOOTCOMPLETIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

using namespace WaveNs;

namespace IsleNs
{

class NetworkModelLocalObjectManager;

class NetworkModelLocalBootCompletionWorker : public WaveWorker
{
    private :
    protected :
    public :
                 NetworkModelLocalBootCompletionWorker (NetworkModelLocalObjectManager *pNetworkModelLocalObjectManager);
        virtual ~NetworkModelLocalBootCompletionWorker ();

        // Now the data members

    private :
    protected :
    public :
};
}

#endif // NETWORKMODELLOCALBOOTCOMPLETIONWORKER_H
