/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVECONFIGURATIONSEGMENTWORKER_H
#define WAVECONFIGURATIONSEGMENTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/WaveMutex.h"

namespace WaveNs
{

class ManagementInterfaceMessage;
class WaveConfigurationSegmentCreateContext;
class WaveConfigurationSegmentDeleteContext;

class WaveConfigurationSegmentWorker : public WaveWorker
{
    private:
    protected:
    public: 
                    WaveConfigurationSegmentWorker  (WaveObjectManager *pWaveObjectManager, const string &configurationSegmentName, const bool isConfigExistValidationRequired = true);
                   ~WaveConfigurationSegmentWorker  ();

        void                                        setConfigurationSegmentName     (const string &configurationSegmentName);
        string                                      getConfigurationSegmentName     () const;
    
        virtual     ManagementInterfaceMessage *    createConfig                    (WaveConfigurationSegmentCreateContext *pWaveConfigurationSegmentCreateContext);
        void                        createConfigValidation ();

        ManagementInterfaceMessage *updateConfig ();
        void                        updateConfigValidation ();
        
        virtual ManagementInterfaceMessage *deleteConfig (WaveConfigurationSegmentDeleteContext *pWaveConfigurationSegmentDeleteContext);

        void                        deleteConfigValidation ();

        bool                        getIsConfigExistValidationRequired () const;
        void                        setIsConfigExistValidationRequired (const bool isConfigExistValidationRequired);

        virtual     string			getErrorString(ManagementInterfaceMessage* pMessage);

    // Data Members 
    private:
        string      m_configurationSegmentName;
        bool        m_isConfigExistValidationRequired;
    protected:
    public: 

};

}

#endif
