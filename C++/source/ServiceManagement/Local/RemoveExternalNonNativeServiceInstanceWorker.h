/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REMOVEEXTERNALNONNATIVESERVICEINSTANCEWORKER_H
#define REMOVEEXTERNALNONNATIVESERVICEINSTANCEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class RemoveExternalNonNativeServiceInstanceMessage;
class RemoveExternalNonNativeServiceInstanceContext;

class RemoveExternalNonNativeServiceInstanceWorker : public WaveWorker
{
    private :
        WaveMessage       *createMessageInstance       (const UI32 &operationCode);

        void addExternalNonNativeServiceInstanceRequestHandler (RemoveExternalNonNativeServiceInstanceMessage *pRemoveExternalNonNativeServiceInstanceMessage);
        void validateStep                                      (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext);
        void deleteShardDataStep                               (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext);
        void deleteStep                                        (RemoveExternalNonNativeServiceInstanceContext *pRemoveExternalNonNativeServiceInstanceContext);

    protected :
    public :
                 RemoveExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~RemoveExternalNonNativeServiceInstanceWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // REMOVEEXTERNALNONNATIVESERVICEINSTANCEWORKER_H
