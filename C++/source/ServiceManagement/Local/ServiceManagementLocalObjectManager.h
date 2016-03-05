/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H
#define SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class ServiceManagementLocalObjectManager : public WaveObjectManager
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
    protected:
    public:
};

}

#endif // SERVICEMANAGEMENTLOCALOBJECTMANAGEROBJECTMANAGER_H
