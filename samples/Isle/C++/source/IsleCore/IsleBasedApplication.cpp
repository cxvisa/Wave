/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "IsleCore/Isle.h"
#include "IsleResourceIdEnums.h"

using namespace IsleNs;

extern "C" int waveMain (int argc, char *argv[]);

extern "C" int isleMain (int argc, char *argv[], int argc1, char *argv1[])
{
    IsleNs::initializeIsleResourceIds ();

    Isle::initialize ();

    return (waveMain (argc, argv));
}
