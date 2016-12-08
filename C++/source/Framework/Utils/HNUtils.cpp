/***************************************************************************
 *   Copyright (C) 20016 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/HNUtils.h"

namespace WaveNs
{

UI64 HNUtils::htonll (UI64 input)
{
    static const int testCandidate = 42;

    // Check endianness and modify if needed

    if (*reinterpret_cast<const char*>(&testCandidate) == testCandidate)
    {
        const UI32 msb = htonl (static_cast<uint32_t> (input >> 32));
        const UI32 lsb = htonl (static_cast<uint32_t> (input & 0xFFFFFFFFLL));

        return (((static_cast<UI64> (lsb) << 32)) | msb);
    }
    else
    {
        return input;
    }
}

}
