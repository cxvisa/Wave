/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERBASEDEVENT_H
#define WAVEBROKERBASEDEVENT_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class WaveBrokerBasedEvent : public SerializableObject
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        WaveBrokerBasedEvent (const string &topic);
        virtual        ~WaveBrokerBasedEvent ();

                string  getTopic             () const;
                void    setTopic             (const string &topic);

    // Now the data members

    private :
        string m_topic;

    protected :
    public :
};

}

#endif // WAVEBROKERBASEDMESSAGE_H
