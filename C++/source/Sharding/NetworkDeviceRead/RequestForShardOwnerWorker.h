/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REQUESTFORSHARDOWNERWORKER_H
#define REQUESTFORSHARDOWNERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class RequestForShardOwnerMessage;
class RequestForShardOwnerContext;

class RequestForShardOwnerWorker : public WaveWorker
{
    private :
        WaveMessage *createMessageInstance (const UI32 &operationCode);

        void requestForShardOwnerRequestHandler (RequestForShardOwnerMessage *pRequestForShardOwnerMessage);
        void validateStep                       (RequestForShardOwnerContext *pRequestForShardOwnerContext);
        void createStep                         (RequestForShardOwnerContext *pRequestForShardOwnerContext);

    protected :
    public :
                 RequestForShardOwnerWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~RequestForShardOwnerWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // REQUESTFORSHARDOWNERWORKER_H

