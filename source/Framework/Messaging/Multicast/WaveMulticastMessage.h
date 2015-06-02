/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMULTICASTMESSAGE_H
#define WAVEMULTICASTMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class WaveMulticastMessage : public SerializableObject
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        WaveMulticastMessage (const string &topic);
        virtual        ~WaveMulticastMessage ();

                string  getTopic             () const;
                void    setTopic             (const string &topic);

    // Now the data members

    private :
        string m_topic;

    protected :
    public :
};

}

#endif // WAVEMULTICASTMESSAGE_H
