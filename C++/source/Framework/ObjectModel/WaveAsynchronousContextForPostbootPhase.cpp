/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveAsynchronousContextForPostbootPhase.h"

namespace WaveNs
{

WaveAsynchronousContextForPostbootPhase::WaveAsynchronousContextForPostbootPhase (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext)
    : WaveAsynchronousContextForBootPhases (pCaller, pCallback, pCallerContext),
      m_passNum                (0)
{
}

WaveAsynchronousContextForPostbootPhase::~WaveAsynchronousContextForPostbootPhase ()
{
}

SI8 WaveAsynchronousContextForPostbootPhase::getPassNum () const
{
    return (m_passNum);
}

void WaveAsynchronousContextForPostbootPhase::setPassNum (SI8 passNum)
{
    m_passNum = passNum;
}

string WaveAsynchronousContextForPostbootPhase::getPassName () const
{
    return (m_passName);
}

void WaveAsynchronousContextForPostbootPhase::setPassName (string passName)
{
    m_passName = passName;
}

UI32 WaveAsynchronousContextForPostbootPhase::getSlotNum () const
{
    return (m_slotNum);
}

void WaveAsynchronousContextForPostbootPhase::setSlotNum (UI32 slotNum)
{
    m_slotNum = slotNum;
}

UI32 WaveAsynchronousContextForPostbootPhase::getRecoveryType () const
{
    return (m_recoveryType);
}

void WaveAsynchronousContextForPostbootPhase::setRecoveryType (UI32 recoveryType)
{
    m_recoveryType = recoveryType;
}

}
