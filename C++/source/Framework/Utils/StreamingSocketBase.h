/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef STREAMINGSOCKETBASE_H
#define STREAMINGSOCKETBASE_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/FixedSizeBuffer.h"
#include "Framework/ObjectModel/SerializableObject.h"

using namespace std;

namespace WaveNs
{

class StreamingSocketBase
{
    private :
    protected :
    public :
                       StreamingSocketBase                (const SI32 maximumNumberOfConnections);
                       StreamingSocketBase                ();
        virtual       ~StreamingSocketBase                ();

                bool   isValid                            ();

        virtual bool   bind                               (const SI32 port) = 0;
        virtual bool   accept                             (StreamingSocketBase &newStreamingSocketBase) = 0;
        virtual bool   connect                            (const string &host, const SI32 port) = 0;
                bool   listen                             ();

                SI32   send                               (const UI32 &value);
                SI32   send                               (const string &dataString);
                SI32   send                               (const FixedSizeBuffer &fixedSizeBuffer);
                SI32   send                               (SerializableObject *pSerializableObjct);
				SI32   send                               (UI8 *pBuffer, const UI32 maximumBufferLength);
                bool   receive                            (string &dataString);
                SI32   receive                            (UI8 *pBuffer, const UI32 maximumBufferLength);
                SI32   receiveAll                         (UI8 *pBuffer, const UI32 maximumBufferLength);
                bool   receiveUI32                        (UI32 &value);

                void   setSocket                          (const SI32 &socket);
                SI32   getSocket                          () const;

                void   setMessageVersionAndSerializationType    (const string& toMessageVersion = "", const UI8& serializationType = SERIALIZE_WITH_ATTRIBUTE_NAME);
                string getMessageVersion                        () const;
                UI8    getSerializationType                     () const;



    // Now the data members

    private :
    protected :
                     SI32 m_socket;
                     SI32 m_maximumNumberOfConnections;

        static const UI32 s_maximumDataLengthToReceive    = 4 * 1024; // 4 KB - We will read 4 KB at a time - but there is no limit on the message size that can be sent across.
                     string m_toMessageVersion;
                     UI8    m_toSerializationType;

    public :
};

}

#endif // STREAMINGSOCKETBASE_H
