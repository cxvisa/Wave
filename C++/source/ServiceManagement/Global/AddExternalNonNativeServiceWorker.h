/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ADDEXTERNALNONNATIVESERVICEWORKERWORKER_H
#define ADDEXTERNALNONNATIVESERVICEWORKERWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class AddExternalNonNativeServiceMessage;
class AddExternalNonNativeServiceContext;

class AddExternalNonNativeServiceWorker : public WaveWorker
{
    private :
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

#endif // ADDEXTERNALNONNATIVESERVICEWORKERWORKER_H
