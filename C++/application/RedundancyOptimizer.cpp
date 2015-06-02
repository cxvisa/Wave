/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <iostream>
#include "Framework/Types/Types.h"
#include "Framework/Redundancy/RedundancyOptimizerBase.h"

using namespace std;
using namespace WaveNs;

int main (int argc, char *argv[])
{
    SI32           i;
    vector<string> argumentVector;

    for (i = 0; i < argc; i++)
    {
        argumentVector.push_back (argv[i]);
    }

    RedundancyOptimizerBase::optimizePathDebugShellEntree (argc, argumentVector);

    return (0);
}
