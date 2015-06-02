/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORSLOTFAILOVER_H
#define WAVEASYNCHRONOUSCONTEXTFORSLOTFAILOVER_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForSlotFailover : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForSlotFailover (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForSlotFailover ();

                UI32            getSlotNumber                          () const;
                void            setSlotNumber                          (const UI32 slotNumber);
                
    // Now the data members

    private :
        UI32        m_slotNumber;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORSLOTFAILOVER_H
