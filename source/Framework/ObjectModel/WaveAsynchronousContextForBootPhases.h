/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORBOOTPHASES_H
#define WAVEASYNCHRONOUSCONTEXTFORBOOTPHASES_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForBootPhases (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForBootPhases ();

                WaveBootReason  getBootReason                        () const;
                void            setBootReason                        (const WaveBootReason &bootReason);
            
                bool            getRollBackFlag                      () const;
                void            setRollBackFlag                      (const bool &rollBackFlag);
    // Now the data members

    private :
        WaveBootReason m_bootReason;
        bool           m_rollBackFlag;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORBOOTPHASES_H
