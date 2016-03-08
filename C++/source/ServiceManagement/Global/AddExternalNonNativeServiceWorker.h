/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEWORKER_H
#define ADDEXTERNALNONNATIVESERVICEWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class AddExternalNonNativeServiceMessage;
class AddExternalNonNativeServiceContext;

class AddExternalNonNativeServiceWorker : public WaveWorker
{
    private :
        WaveMessage       *createMessageInstance       (const UI32 &operationCode);
        WaveManagedObject *createManagedObjectInstance (const string &managedClassName);

        void addExternalNonNativeServiceRequestHandler (AddExternalNonNativeServiceMessage *pAddExternalNonNativeServiceMessage);
        void validateStep                              (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext);
        void createStep                                (AddExternalNonNativeServiceContext *pAddExternalNonNativeServiceContext);

    protected :
    public :
                 AddExternalNonNativeServiceWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~AddExternalNonNativeServiceWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // ADDEXTERNALNONNATIVESERVICEWORKER_H
