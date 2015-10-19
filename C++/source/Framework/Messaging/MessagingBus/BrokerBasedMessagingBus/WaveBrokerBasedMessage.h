/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEBROKERBASEDMESSAGE_H
#define WAVEBROKERBASEDMESSAGE_H

#include "Framework/ObjectModel/SerializableObject.h"

namespace WaveNs
{

class WaveBrokerBasedMessage : public SerializableObject
{
    private :
        class WaveBrokerBasedMessageBuffer
        {
            private :
            protected :
            public :
                                              WaveBrokerBasedMessageBuffer (UI32 size, const void *pBuffer, bool ownedByMesage = false);
                                              WaveBrokerBasedMessageBuffer (const WaveBrokerBasedMessageBuffer &waveMessagebuffer);
                                             ~WaveBrokerBasedMessageBuffer ();
                WaveBrokerBasedMessageBuffer  &operator =                  (const WaveBrokerBasedMessageBuffer &waveMessageBuffer);

                void                           destroy                     ();
                UI32                           getSize                     () const;
                void                          *getPBuffer                  () const;
                void                           setPBuffer                  (void *pBuffer);
                void                           invalidateBuffer            ();

            // Now the data members

            private :
                UI32  m_size;
                void *m_pBuffer;

            protected :
            public :
        };

    protected :
        void setupAttributesForSerialization  ();

    public :
                                            WaveBrokerBasedMessage         ();
                                            WaveBrokerBasedMessage         (const WaveBrokerBasedMessageType &waveBrokerBasedMessageType);
        virtual                            ~WaveBrokerBasedMessage         ();

                WaveBrokerBasedMessageType  getWaveBrokerBasedMessageType  () const;
                void                        setWaveBrokerBasedMessageType  (const WaveBrokerBasedMessageType &waveBrokerBasedMessageType);


                UI32                         getNumberOfBuffers            () const;
                void                         getBufferTags                 (vector<UI32> &bufferTagsVector) const;

        virtual WaveMessageStatus            addBuffer                     (UI32 tag, UI32 size, const void *pBuffer, bool bufferWillBeOwnedByMessage = false);
        virtual void                        *findBuffer                    (UI32 tag, UI32 &size) const;
        virtual void                        *transferBufferToUser          (UI32 tag, UI32 &size);
        virtual WaveMessageStatus            removeBuffer                  (UI32 tag);
                void                         removeAllBuffers              ();
                void                         transferAllBuffers            (WaveBrokerBasedMessage *pWaveBrokerBasedMessage);

        static  WaveBrokerBasedMessageType   getWaveBrokerBasedMessageType (const char *pSerializedData);
        static  string                       getTopicName                  (const char *pSerializedData);



    // Now the data members

    private :
        WaveBrokerBasedMessageType                 m_waveBrokerBasedMessageType;
        map<UI32, WaveBrokerBasedMessageBuffer *>  m_buffers;

    protected :
    public :
};

}

#endif // WAVEBROKERBASEDMESSAGE_H
