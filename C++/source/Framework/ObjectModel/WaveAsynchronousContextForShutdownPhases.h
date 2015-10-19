/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORSHUTDOWNPHASES_H
#define WAVEASYNCHRONOUSCONTEXTFORSHUTDOWNPHASES_H

#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForShutDownPhases : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForShutDownPhases (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForShutDownPhases ();

                WaveShutDownReason  getShutDownReason                        () const;
                void                setShutDownReason                        (const WaveShutDownReason &shutDownReason);

    // Now the data members

    private :
        WaveShutDownReason m_shutDownReason;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORSHUTDOWNPHASES_H
