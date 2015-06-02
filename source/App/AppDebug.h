/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef APPDEBUG_H
#define APPDEBUG_H

#include "App/AppInterface.h"
#include <string>
#include <vector>

namespace WaveNs
{


typedef struct dupBuffer_t
{
    char  *pFirstData;
    UI32   firstDataLen;
    char  *pSecondData;
    UI32   secondDataLen;
} dupBuffer_t;

class AppDebug
{
    private :
    protected :
    public :
                         AppDebug  ();
                        ~AppDebug  ();
        static  void     initialize    ();

        static  UI32     shellExecuteDuplicateCmdDebug      (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteRegisterCallBackDebug  (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteSendDupCmdReplyDebug   (UI32 argc, vector<string> argv);
        // Now the data members

    private :

    protected :
    public :
};


}

#endif // APPDEBUG_H
