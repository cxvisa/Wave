/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONSERVICEMESSAGES_H
#define REGRESSIONSERVICEMESSAGES_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "Framework/Types/Types.h"
#include "Regression/RegressionTestEntry.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"
#include <vector>

namespace WaveNs
{

class RegressionTestObjectManagerGetTestServiceEntriesMessage : public ManagementInterfaceMessage
{
    private :
        void setNumberOfTestServiceEntries (UI32 numberOfTestServiceEntries);
        void addTestServiceEntry           (const WaveServiceId &prismServiceId, const bool &isServiceEnabled);

    protected :
    public :
                                     RegressionTestObjectManagerGetTestServiceEntriesMessage ();
        virtual                     ~RegressionTestObjectManagerGetTestServiceEntriesMessage ();
        virtual void                 setupAttributesForSerialization                         ();

                UI32                 getNumberOfTestServiceEntries                           ();
                RegressionTestEntry  getTestServiceEntryAt                                   (UI32 index);

    // Now the data members

    private :
        UI32         m_numberOfTestServiceEntries;
        vector<UI32> m_testServiceIds;
        vector<bool> m_testServiceStates;

    protected :
    public:

        friend class RegressionTestObjectManager;
};

class RegressionTestObjectManagerSetTestServiceStateMessage : public PrismMessage
{
    private :
    protected :
    public :
                                RegressionTestObjectManagerSetTestServiceStateMessage ();
                                RegressionTestObjectManagerSetTestServiceStateMessage (WaveServiceId testseviceId, bool isTestEnabled);
        virtual                ~RegressionTestObjectManagerSetTestServiceStateMessage ();
        virtual void            setupAttributesForSerialization                       ();
                WaveServiceId  getTestServiceId                                      ();
                bool            getIsTestEnabled                                      ();

    // Now the data members

    private :
        WaveServiceId m_testServiceId;
        bool           m_isTestEnabled;

    protected :
    public :
};

class RegressionTestObjectManagerStartRegressionMessage : public PrismMessage
{
    private :
    protected :
    public :
                      RegressionTestObjectManagerStartRegressionMessage ();
                      RegressionTestObjectManagerStartRegressionMessage (UI32 numberOfTimesToRunRegression);
        virtual      ~RegressionTestObjectManagerStartRegressionMessage ();
        virtual void  setupAttributesForSerialization                   ();
        UI32          getNumberOfTimesToRunRegression                   ();

    // Now the data members

    private :
        UI32 m_numberOfTimesToRunRegression;

    protected :
    public :
};

class RegressionTestObjectManagerRunTestForAServiceMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                                RegressionTestObjectManagerRunTestForAServiceMessage ();
                                RegressionTestObjectManagerRunTestForAServiceMessage (WaveServiceId serviceCode);
                                RegressionTestObjectManagerRunTestForAServiceMessage (WaveServiceId serviceCode, UI32 numberOfTimesToRunServiceTest);
        virtual                ~RegressionTestObjectManagerRunTestForAServiceMessage ();
        virtual void            setupAttributesForSerialization                      ();
                WaveServiceId  getServiceCode                                       ();
                UI32            getNumberOfTimesToRunServiceTest                     ();

    // Now the data members

    private :
        WaveServiceId m_serviceCode;
        UI32           m_numberOfTimesToRunServiceTest;

    protected :
    public :
};

class RegressionTestObjectManagerPrepareTestForAServiceMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                                RegressionTestObjectManagerPrepareTestForAServiceMessage ();
                                RegressionTestObjectManagerPrepareTestForAServiceMessage (WaveServiceId serviceCode);
                                RegressionTestObjectManagerPrepareTestForAServiceMessage (WaveServiceId serviceCode, vector<string> inputStrings);
        virtual                ~RegressionTestObjectManagerPrepareTestForAServiceMessage ();
        virtual void            setupAttributesForSerialization                      ();
                WaveServiceId  getServiceCode                                       ();
                vector<string> &getInputStrings                                      ();

    // Now the data members

    private :
        WaveServiceId m_serviceCode;
        vector<string> m_inputStrings;

    protected :
    public :
};

}

#endif // REGRESSIONSERVICEMESSAGES_H
