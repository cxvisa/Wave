/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REDUNDANCYOPTIMIZER64WITHVARIABLECHUNKING_H
#define REDUNDANCYOPTIMIZER64WITHVARIABLECHUNKING_H

#include <string>
#include <map>
#include "Framework/Utils/FixedSizeBuffer.h"
#include "Mathematics/Z2/Z2.h"
#include "Framework/Redundancy/RedundancyOptimizer64.h"

using namespace std;

namespace WaveNs
{

class RedundancyOptimizer64WithVariableChunking : public RedundancyOptimizer64
{
    private :
    protected :
    public :
                       RedundancyOptimizer64WithVariableChunking ();
        virtual       ~RedundancyOptimizer64WithVariableChunking ();

        virtual void   optimizeFile                              (const string &fileName);

                UI32   getMinimumChunkSize                       () const;
                void   setMinimumChunkSize                       (const UI32 &minimumChunkSize);
                UI32   getMaximumChunkSize                       () const;
                void   setMaximumChunkSize                       (const UI32 &maximumChunkSize);
                UI64   getMagicFingerPrint                       () const;
                void   setMagicFingerPrint                       (const UI64 &magicFingerPrint);
                UI32   getMagicFingerPrintSize                   () const;
                void   setMagicFingerPrintSize                   (const UI32 &magicFingerPrintSize);
                UI64   getMagicFingerPrintBitMask                () const;
                void   setMagicFingerPrintBitMask                (const UI64 &magicFingerPrintBitMask);

        virtual void   print                                     ();

    // Now the data members

    private :
        UI32 m_minimumChunkSize;
        UI32 m_maximumChunkSize;
        UI64 m_magicFingerPrint;
        UI32 m_magicFingerPrintSize;
        UI64 m_magicFingerPrintBitMask;

        UI64 m_anchorFingerPrintMatches;
        UI64 m_maximumChunkSizeMatches;
        UI64 m_residueMatches;

    protected :
    public :
};

}

#endif // REDUNDANCYOPTIMIZER64WITHVARIABLECHUNKING_H
