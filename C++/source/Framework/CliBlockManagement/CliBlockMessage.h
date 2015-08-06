/***************************************************************************
 *   Copyright (C) 2013      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#ifndef CLIBLOCKMESSAGE_H
#define CLIBLOCKMESSAGE_H 

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class CliBlockDetail;
class CliBlockMessage : public WaveMessage
{
    private :
    protected :
               void                     setupAttributesForSerialization     ();

    public :
                                        CliBlockMessage                     ();
                                        CliBlockMessage                     (bool operation, const CliBlockDetail& cliBlockDetail);
        virtual                        ~CliBlockMessage                     ();

         const bool                     getOperation                        () const;
         const ResourceId               getReason                           () const;
         const LocationId               getOriginator                       () const;
         const WaveServiceId           getWaveServiceId                   () const;

    // Now the data members

    private :
        bool                m_operation; //true is block, false is unblock
        ResourceId          m_reason;
        LocationId          m_originator;
        WaveServiceId      m_waveServiceId;

    protected :
    public :
};

}

#endif // CLIBLOCKMESSAGE_H
