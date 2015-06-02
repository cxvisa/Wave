/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGEPAYLOADBASE_H
#define WAVEMESSAGEPAYLOADBASE_H

#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class WaveMessagePayloadBase
{
    private :
    protected :
        void addSerializableAttribute (Attribute *pAttribute);

    public :
         WaveMessagePayloadBase (PrismMessage *pPrismMessage);
        ~WaveMessagePayloadBase ();

    // now the data members

    private :
        PrismMessage *m_pPrismMessage;

    protected :
    public :
};

}

#endif // WAVEMESSAGEPAYLOADBASE_H
