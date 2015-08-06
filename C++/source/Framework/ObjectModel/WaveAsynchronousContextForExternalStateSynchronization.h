/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFOREXTERNALSTATESYNCHRONIZATION_H
#define WAVEASYNCHRONOUSCONTEXTFOREXTERNALSTATESYNCHRONIZATION_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForExternalStateSynchronization: public PrismAsynchronousContext
{
    private :
    protected :
    public :
                                WaveAsynchronousContextForExternalStateSynchronization (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                ~WaveAsynchronousContextForExternalStateSynchronization ();

                UI32            getFssStageNumber                                      () const;
                void            setFssStageNumber                                      (const UI32 fssStageNumber);
                
                ResourceId      getServiceType                                         () const;
                void            setServiceType                                         (const ResourceId serviceType);

    // Now the data members

    private :
        UI32        m_fssStageNumber;
        ResourceId  m_serviceType;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFOREXTERNALSTATESYNCHRONIZATION_H
