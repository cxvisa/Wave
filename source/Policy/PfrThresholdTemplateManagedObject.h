/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDTEMPLATEMANAGEDOBJECT_H
#define PFRTHRESHOLDTEMPLATEMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Types/Types.h"

namespace WaveNs
{

class PolicyObjectManager;

class PfrThresholdTemplateManagedObject : public WaveManagedObject
{
    private :
    protected :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();
        void setupKeys                     ();

    public :
                        PfrThresholdTemplateManagedObject (PolicyObjectManager *pPolicyObjectManager);
        virtual        ~PfrThresholdTemplateManagedObject ();

        static  string  getClassName                      ();

                SI32    getLossRate                       () const;
                void    setLossRate                       (const SI32 &lossRate);
                SI32    getOneWayDelay                    () const;
                void    setOneWayDelay                    (const SI32 &oneWayDelay);
                SI32    getJitter                         () const;
                void    setJitter                         (const SI32 &jitter);
                SI32    getLossRatePriority               () const;
                void    setLossRatePriority               (const SI32 &lossRatePriority);
                SI32    getOneWayDelayPriority            () const;
                void    setOneWayDelayPriority            (const SI32 &oneWayDelayPriority);
                SI32    getJitterPriority                 () const;
                void    setJitterPriority                 (const SI32 &jitterPriority);

    // Now the data members

    private :
        SI32 m_lossRate;
        SI32 m_oneWayDelay;
        SI32 m_jitter;
        SI32 m_lossRatePriority;
        SI32 m_oneWayDelayPriority;
        SI32 m_jitterPriority;

    protected :
    public :
};

}

#endif // PFRTHRESHOLDTEMPLATEMANAGEDOBJECT_H

