/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "NetworkModel/Local/BootCompletion/NetworkModelLocalBootCompletionWorker.h"
#include "NetworkModel/Local/NetworkModelLocalObjectManager.h"

namespace IsleNs
{

NetworkModelLocalBootCompletionWorker::NetworkModelLocalBootCompletionWorker (NetworkModelLocalObjectManager *pNetworkModelLocalObjectManager)
    : WaveWorker (pNetworkModelLocalObjectManager)
{
}

NetworkModelLocalBootCompletionWorker::~NetworkModelLocalBootCompletionWorker ()
{
}

}
