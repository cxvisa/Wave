/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERBASEDMESSAGEPAYLOAD_H
#define WAVEBROKERBASEDMESSAGEPAYLOAD_H

#include "Framework/Types/Types.h"

#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveBrokerBasedMessagePayload
{
    private :
    protected :
    public :
                        WaveBrokerBasedMessagePayload  ();
                       ~WaveBrokerBasedMessagePayload  ();

        UI32           &getMessageBodySize             ();
        char          *&getMessageBody                 ();
        vector<UI32>   &getBufferTags                  ();
        vector<UI32>   &getBufferSizes                 ();
        vector<UI8 *>  &getBuffers                     ();

        void            prepareAndGetIovecToPostOnWire (struct iovec **pIoVector, UI32 &ioVectorCount);

    // Now the data members

    private :
        UI32          m_messageBodySize;
        char         *m_pMessageBody;
        vector<UI32>  m_bufferTags;
        vector<UI32>  m_bufferSizes;
        vector<UI8 *> m_buffers;
        UI32          m_numberOfBuffers;
        bool          m_isPreparedForPostingOnWire;

        struct iovec *m_pIoVector;
        UI32           m_ioVectorCount;

    protected :
    public :
};

}

#endif // WAVEBROKERBASEDMESSAGEPAYLOAD_H
