/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H
#define WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H

#include "Framework/Types/Types.h"
#include "Framework/Utils/WaveAsynchronousContext.h"

namespace WaveNs
{

class WaveAsynchronousContextForDebugInformation : public WaveAsynchronousContext
{
    private :
    protected :
    public :
                                    WaveAsynchronousContextForDebugInformation  (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                    ~WaveAsynchronousContextForDebugInformation  ();

                void                setDebugInformation                         (const string &debugInformation);
                const   string &    getDebugInformation                         () const;

    // Now the data members

    private :
                        string      m_debugInformation;

    protected :
    public :
};

}

#endif // WAVEASYNCHRONOUSCONTEXTFORDEBUGINFORMATION_H
