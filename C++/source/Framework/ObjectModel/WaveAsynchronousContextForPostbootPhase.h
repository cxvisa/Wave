/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORPOSTBOOTPHASE_H
#define WAVEASYNCHRONOUSCONTEXTFORPOSTBOOTPHASE_H

#include "Framework/ObjectModel/WaveAsynchronousContextForBootPhases.h"
#include "Framework/ObjectModel/WavePostBootEvent.h"

namespace WaveNs
{

class WaveAsynchronousContextForPostbootPhase : public WaveAsynchronousContextForBootPhases
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForPostbootPhase (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForPostbootPhase ();

                SI8             getPassNum                           () const;
                void            setPassNum                           (SI8 passNum);
                string          getPassName                          () const;
                void            setPassName                          (string passName);
                UI32            getSlotNum                           () const;
                void            setSlotNum                           (UI32 slotNum);
                UI32            getRecoveryType                      () const;
                void            setRecoveryType                      (UI32 recoveryType);
    // Now the data members

    private :
                SI8             m_passNum; // indicates postboot pass#
                string          m_passName;
                UI32            m_slotNum;
                UI32            m_recoveryType;
    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORPOSTBOOTPHASE_H
