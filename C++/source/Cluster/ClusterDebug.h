/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef CLUSTERDEBUG_H
#define CLUSTERDEBUG_H

#include "App/AppInterface.h"
#include <string>
#include <vector>

namespace WaveNs
{

class ClusterDebug
{
    private :
    protected :
    public :
                         ClusterDebug  ();
                        ~ClusterDebug  ();
                void     initialize    ();

        static  UI32     shellExecuteCreateClusterDebug     (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteShowStatDebug          (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteLocatHeartBeatDebug    (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteRegisterCallBackDebug  (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteAddNodeDebug           (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteJoinNodeDebug          (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteRemoveNodeDebug        (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteGetRoleDebug           (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteConfigHeartBeatDebug   (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteRemoveClusterDebug     (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteGetClusterConfigDebug  (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteGetClusterInfoDebug    (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteMakeThisNodePrincipal  (UI32 argc, vector<string> argv);
        static  UI32     shellExecuteNodifySecondaryNodeFailure  (UI32 argc, vector<string> argv);
        // Now the data members

    private :

    protected :
    public :
};


}

#endif // CLUSTERDEBUG_H
