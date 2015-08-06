/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka, Jayanth Venkataraman              *
 ***************************************************************************/

#ifndef WAVESYSYEMMANAGEMENTOBJECTMANAGER_H
#define WAVESYSYEMMANAGEMENTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"
#include "Modeling/YANG/ObjectModel/YangModuleCollection.h"
#include "Modeling/YANG/ObjectModel/YangUserInterface.h"

namespace WaveNs
{

class WaveSystemManagementDisplayConfigurationWorker;
class WaveSystemManagementGetYangUserInterfaceWorker;
class WaveSystemManagementYangInterfacesInitializeWorker; 
class WaveSystemManagementGetPossibleCompletionsWorker;
class WaveSystemManagementGatewayWorker;

class WaveSystemManagementObjectManager : public WaveLocalObjectManager
{
    private :
             WaveSystemManagementObjectManager       ();


    protected :
    public :
        virtual                                   ~WaveSystemManagementObjectManager    ();
        static  WaveSystemManagementObjectManager *getInstance                          ();
        static  WaveServiceId                     getWaveServiceId                    ();
        static  string                             getClassName                         ();

        static  YangModuleCollection              *getYangModuleCollection              ();

        static  YangUserInterface                 *getYangUserInterface                 ();
        static  YangUserInterface                 *getClonedYangUserInterface           ();
        static  void                               getYinForYangUserInterface           (string &yinForYangUserInterface);


    // Now the data members

    private :
        WaveSystemManagementDisplayConfigurationWorker     *m_pWaveSystemManagementDisplayConfigurationWorker;
        WaveSystemManagementGetYangUserInterfaceWorker     *m_pWaveSystemManagementGetYangUserInterfaceWorker;
        WaveSystemManagementYangInterfacesInitializeWorker *m_pWaveSystemManagementYangInterfacesInitializeWorker;
        WaveSystemManagementGetPossibleCompletionsWorker   *m_pWaveSystemManagementGetPossibleCompletionsWorker;
        WaveSystemManagementGatewayWorker                  *m_pWaveSystemManagementGatewayWorker;

    protected :
    public :
};

}

#endif // WAVESYSYEMMANAGEMENTOBJECTMANAGER_H
