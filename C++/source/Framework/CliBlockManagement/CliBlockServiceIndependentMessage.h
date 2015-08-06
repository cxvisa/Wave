/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#ifndef CLIBLOCKSERVICEINDEPENDENTMESSAGE_H
#define CLIBLOCKSERVICEINDEPENDENTMESSAGE_H 

#include "Framework/Messaging/Local/WaveServiceIndependentMessage.h"

namespace WaveNs
{

class CliBlockMessage;
class CliBlockServiceIndependentMessage : public WaveServiceIndependentMessage
{
    private :
    protected :
               void                     setupAttributesForSerialization     ();

    public :
                                        CliBlockServiceIndependentMessage                     ();
                                        CliBlockServiceIndependentMessage                     (const CliBlockMessage &cliBlockMessage);
        virtual                        ~CliBlockServiceIndependentMessage                     ();

         const bool                     getOperation                        () const;
         const ResourceId               getReason                           () const;
         const LocationId               getOriginator                       () const;
         const WaveServiceId           getWaveServiceId                   () const;

    // Now the data members

    private :
        bool                m_operation;
        ResourceId          m_reason;
        LocationId          m_originator;
        WaveServiceId      m_prismServiceId;

    protected :
    public :
};

}

#endif // CLIBLOCKSERVICEINDEPENDENTMESSAGE_H
