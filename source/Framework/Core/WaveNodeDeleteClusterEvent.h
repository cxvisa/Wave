/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef WAVENODEDELETECLUSTEREVENT_H
#define WAVENODEDELETECLUSTEREVENT_H
#include "Framework/Messaging/Local/PrismEvent.h"

namespace WaveNs
{

class WaveNodeDeleteClusterEvent : public PrismEvent
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                 WaveNodeDeleteClusterEvent ();
        virtual ~WaveNodeDeleteClusterEvent ();

        void     setIsRebootRequired        (const bool &isRebootRequired);
        bool     getIsRebootRequired        () const;
    private :

        bool     m_isRebootRequired;
    protected :
    public :
};

}

#endif //WAVENODEDELETECLUSTEREVENT_H
