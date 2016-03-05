/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVICEMANAGEMENTOBJECTMANAGEROBJECTMANAGER_H
#define SERVICEMANAGEMENTOBJECTMANAGEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class AddExternalNonNativeServiceWorker;

class ServiceManagementObjectManager : public WaveObjectManager
{
    private:
        ServiceManagementObjectManager ();

    protected:
    public:
        virtual ~ServiceManagementObjectManager ();

        static ServiceManagementObjectManager *getInstance      ();
        static WaveServiceId                   getWaveServiceId ();
        static string                          getServiceName   ();

        // Now the Data Members

    private:
        AddExternalNonNativeServiceWorker *m_pAddExternalNonNativeServiceWorker;

    protected:
    public:
};

}

#endif // SERVICEMANAGEMENTOBJECTMANAGEROBJECTMANAGER_H
