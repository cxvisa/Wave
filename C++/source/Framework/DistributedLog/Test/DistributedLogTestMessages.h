/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGTESTMESSAGES_H
#define DISTRIBUTEDLOGTESTMESSAGES_H

#include "Framework/Messaging/Local/WaveMessage.h"


namespace WaveNs
{

class DistributedLogInvokeAddLogApiMessage : public WaveMessage
{
    private:
                void            setupAttributesForSerialization         ();
    protected:
    public:
                                DistributedLogInvokeAddLogApiMessage    ();
        virtual                ~DistributedLogInvokeAddLogApiMessage    ();
                ResourceId      getLogType                              ();
                void            setLogType                              (ResourceId logType);
                ResourceId      getLogDescriptionType                   ();
                void            setLogDescriptionType                   (ResourceId logDescriptionType);
                ObjectId        getManagedObjectId                      ();
                void            setManagedObjectId                      (ObjectId managedObjectId);
                UI32            getNumberOfLogsToAdd                    ();
                void            setNumberOfLogsToAdd                    (UI32 numberOfLogsToAdd);

    // Now the data members
    private:
                ResourceId      m_logType;
                ResourceId      m_logDescriptionType;
                ObjectId        m_managedObjectId;
                UI32            m_numberOfLogsToAdd;
    protected:
    public:
};

}

#endif //DISTRIBUTEDLOGTESTMESSAGES_H
