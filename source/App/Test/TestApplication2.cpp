/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <stdio.h>

extern "C" int testMain2 (int argc, char *argv[], int id)
{
    int i;

//    printf("\n    ######## TEST MAIN 2 ##########\n");
//    printf("argc:%d, argv: ", argc);
    for (i=0; i< argc; i++)
    {
//        printf("%s ", argv[i]);
    }
//    printf(", id:%d\n", id);
    return 0;
}
