/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H
#define SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class AddExternalNonNativeServiceInstanceWorker;
class SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker;
class RemoveExternalNonNativeServiceInstanceWorker;

class ServiceManagementLocalObjectManager : public WaveLocalObjectManager
{
    private:
        ServiceManagementLocalObjectManager ();

    protected:
    public:
        virtual ~ServiceManagementLocalObjectManager ();

        static ServiceManagementLocalObjectManager *getInstance      ();
        static WaveServiceId                        getWaveServiceId ();
        static string                               getServiceName   ();

        // Now the Data Members

    private:
        AddExternalNonNativeServiceInstanceWorker                     *m_pAddExternalNonNativeServiceInstanceWorker;
        SetExternalNonNativeServiceInstanceShardingCapabilitiesWorker *m_pSetExternalNonNativeServiceInstanceShardingCapabilitiesWorker;
        RemoveExternalNonNativeServiceInstanceWorker                  *m_pRemoveExternalNonNativeServiceInstanceWorker;

    protected:
    public:
};

}

#endif // SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H
