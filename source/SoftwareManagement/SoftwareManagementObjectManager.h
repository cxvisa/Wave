/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SOFTWAREMANAGEMENTOBJECTMANAGER_H
#define SOFTWAREMANAGEMENTOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class PrismLinearSequencerContext;
class SoftwareManagementVersionWorker;

class SoftwareManagementObjectManager : public WaveObjectManager
{
    private :
             SoftwareManagementObjectManager ();
        void initialize                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void displayVersionStep              (PrismLinearSequencerContext *pPrismLinearSequencerContext);

    protected :
    public :
        virtual                                 ~SoftwareManagementObjectManager ();
        static  SoftwareManagementObjectManager *getInstance                     ();
        static  PrismServiceId                   getPrismServiceId               ();
        static  string                           getClassName                    ();

    // Now the data members

    private :
        SoftwareManagementVersionWorker *m_pSoftwareManagementVersionWorker;
    protected :
    public :
};

}

#endif // SOFTWAREMANAGEMENTOBJECTMANAGER_H
