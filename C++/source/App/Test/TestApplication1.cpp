/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <stdio.h>
#include "Framework/OsLayer/WaveOsLayer.h"

using namespace WaveNs;

extern "C" int testMain1 (int argc, char *argv[], int id)
{
    int i;

//    printf("\n    ######## TEST MAIN ##########\n");
//    printf("argc:%d, argv: ", argc);
    for (i=0; i< argc; i++)
    {
//        printf("%s ", argv[i]);
    }
//    printf(", id:%d\n", id);

    while (true)
    {
        waveSleep (5);
    }

    return 0;
}
