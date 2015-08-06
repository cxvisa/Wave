/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONWORKER_H
#define WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage;
class WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage;
class DisplayCurrentConfigurationContext;
class WaveManagedObjectQueryContext;

class WaveSystemManagementDisplayConfigurationWorker : public WaveWorker
{
    private :
        virtual WaveMessage *createMessageInstance                                                           (const UI32 &operationCode);

                void displayCurrentConfigurationByQualifiedYangPathHandler                                    (WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage *pWaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage);
                void displayCurrentConfigurationByQualifiedYangPathComputeYangDisplayConfigurationContextStep (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext);
                void displayCurrentConfigurationStep                                                          (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext);
                void displayCurrentConfigurationCallback                                                      (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext);

                void displayCurrentConfigurationByTargetNodeNameHandler                                       (WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage *pWaveSystemManagementDisplayConfigurationByTargetNodeNameMessage);
                void displayCurrentConfigurationByTargetNodeNameComputeYangDisplayConfigurationContextStep    (DisplayCurrentConfigurationContext *pDisplayCurrentConfigurationContext);

    protected :
    public :
                 WaveSystemManagementDisplayConfigurationWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~WaveSystemManagementDisplayConfigurationWorker ();

    // Now the Data Members

    private :
    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONWORKER_H
