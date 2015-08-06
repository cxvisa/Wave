/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGEPAYLOADBASE_H
#define WAVEMESSAGEPAYLOADBASE_H

#include "Framework/Messaging/Local/WaveMessage.h"

namespace WaveNs
{

class WaveMessagePayloadBase
{
    private :
    protected :
        void addSerializableAttribute (Attribute *pAttribute);

    public :
         WaveMessagePayloadBase (WaveMessage *pWaveMessage);
        ~WaveMessagePayloadBase ();

    // now the data members

    private :
        WaveMessage *m_pWaveMessage;

    protected :
    public :
};

}

#endif // WAVEMESSAGEPAYLOADBASE_H
