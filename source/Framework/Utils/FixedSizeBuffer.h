/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FIXEDSIZEBUFFER_H
#define FIXEDSIZEBUFFER_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class FixedSizeBuffer
{
    private :
    protected :
    public :
                    FixedSizeBuffer      (const UI32 maximumSize);
                    FixedSizeBuffer      (const UI32 maximumSize, void *pBuffer, bool isBufferUsed = true);
                   ~FixedSizeBuffer      ();
              UI8  *getPRawBuffer        ();
              UI8  *getPRawBuffer        () const;
              UI8  *getPCurrentRawBuffer ();
        const UI32  getMaximumSize       () const;
        const UI32  getCurrentSize       () const;
        const UI32  getRemainingSize     () const;
              void  incrementCurrentSize (const UI32 incrementSize);
              void  reset                ();
              bool  isFull               ();
        const void  toString             (string &resultString);
              UI8  *transferBufferToUser (UI32 &currentSize, UI32 &maximumSize);

    // Now the data members

    private :
        UI32  m_maximumSize;
        UI8  *m_pRawBuffer;
        UI32  m_currentSize;
        bool  m_isBufferOwnedByMe;

    protected :
    public :
};

}

#endif // FIXEDSIZEBUFFER_H
