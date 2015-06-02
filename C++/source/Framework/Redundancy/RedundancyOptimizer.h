/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REDUNDANCYOPTIMIZER_H
#define REDUNDANCYOPTIMIZER_H

#include <string>
#include <map>
#include "Framework/Utils/FixedSizeBuffer.h"
#include "Mathematics/Z2/Z2.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"

using namespace std;

namespace WaveNs
{

class RedundancyOptimizer : public RedundancyOptimizerBase
{
    private :
        void addUniqueChunk (const string &fingerPrint, char *pBuffer, const UI64 &bufferLength);

    protected :
    public :
                       RedundancyOptimizer     ();
        virtual       ~RedundancyOptimizer     ();

        virtual void   optimizeFile            (const string &fileName);

        virtual void   print                   ();

        virtual void   destroyUniqueChunks     ();

    // Now the data members

    private :
        map<string, FixedSizeBuffer *> m_uniqueChunks;
        map<string, UI64>              m_uniqueChunkCounts;

    protected :
    public :
};

}

#endif // REDUNDANCYOPTIMIZER_H
