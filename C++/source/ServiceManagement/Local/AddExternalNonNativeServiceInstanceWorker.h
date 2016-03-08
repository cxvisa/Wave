/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEINSTANCEWORKER_H
#define ADDEXTERNALNONNATIVESERVICEINSTANCEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class AddExternalNonNativeServiceInstanceMessage;
class AddExternalNonNativeServiceInstanceContext;

class AddExternalNonNativeServiceInstanceWorker : public WaveWorker
{
    private :
        WaveMessage       *createMessageInstance       (const UI32 &operationCode);
        WaveManagedObject *createManagedObjectInstance (const string &managedClassName);

        void addExternalNonNativeServiceInstanceRequestHandler (AddExternalNonNativeServiceInstanceMessage *pAddExternalNonNativeServiceInstanceMessage);
        void validateStep                                      (AddExternalNonNativeServiceInstanceContext *pAddExternalNonNativeServiceInstanceContext);
        void createStep                                        (AddExternalNonNativeServiceInstanceContext *pAddExternalNonNativeServiceInstanceContext);

    protected :
    public :
                 AddExternalNonNativeServiceInstanceWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~AddExternalNonNativeServiceInstanceWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // ADDEXTERNALNONNATIVESERVICEINSTANCEWORKER_H
