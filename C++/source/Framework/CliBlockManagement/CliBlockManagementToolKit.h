/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                *
 ***************************************************************************/

#ifndef CLIBLOCKMANAGEMENTTOOLKIT
#define CLIBLOCKMANAGEMENTTOOLKIT

#include "Framework/CliBlockManagement/CliBlockDetail.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WaveWorker.h"

using namespace std;

namespace WaveNs
{

class CliBlockManagementToolKit
{
    private :

        static ResourceId             blockCli   (const CliBlockDetail &detail);
        static ResourceId             unblockCli (const CliBlockDetail &detail); 

    protected :
    public :

        static bool                   isCliBlocked                                    (vector<ResourceId> &reasons);
        static ResourceId             getCliBlockDetail                               (const ResourceId givenReason, CliBlockDetail &detail);
        static ResourceId             cleanAllBlockedReasons                          ();
        static string                 getDisplayString                                ();

        static PrismMutexStatus       lock                                            ();
        static PrismMutexStatus       unlock                                          ();
        static PrismMutexStatus       tryLock                                         ();

        // Now the data members

    private :
        static map <ResourceId, CliBlockDetail>                                         m_cliBlockMap;
        static PrismMutex                                                               m_cliBlockMapMutex;
        static PrismMutex                                                               m_cliBlockOperationMutex;

    protected :
    public :

    friend class WaveObjectManager;
    friend class WaveWorker;
    friend class ClusterLocalObjectManager;
    friend class CliBlockWorker;


};
}

#endif // CLIBLOCKMANAGEMENTTOOLKIT
