/**
 *@file ClusterLocalSetHardwareSynchronizationMessage.h
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved. 
 *
 * Description: This file declares the message class handled
 *              by ClusterLocalOM which is used for updating
 *              the hardware synchronization state attribute
 *              in the WaveNode Managed Object. 
 *
 * Author :     Brian Adaniya
 * Date :       05/05/2011
 */

#ifndef CLUSTERLOCALSETHARDWARDSYNCHRONIZATIONMESSAGE_H 
#define CLUSTERLOCALSETHARDWARDSYNCHRONIZATIONMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class ClusterLocalSetHardwareSynchronizationStateMessage : public PrismMessage
{
    private :
                void                setupAttributesForSerialization                     ();

    protected :
    public :
                                    ClusterLocalSetHardwareSynchronizationStateMessage  ();
                                    ClusterLocalSetHardwareSynchronizationStateMessage  (ResourceId hardwareSynchronizationState);
        virtual                    ~ClusterLocalSetHardwareSynchronizationStateMessage  ();

                ResourceId          getHardwareSynchronizationState                     () const;
                void                setHardwareSynchronizationState                     (ResourceId hardwareSynchronizationState);

    // Now the data members

    private :
                ResourceId          m_hardwareSynchronizationState;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSETHARDWARDSYNCHRONIZATIONMESSAGE_H

