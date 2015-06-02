/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef POLICYOBJECTMANAGER_H
#define POLICYOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class CategoryWorker;
class PolicyObjectManagerInitializationWorker;
class ApplicationWorker;

class PolicyObjectManager : public WaveObjectManager
{
    private :
                          PolicyObjectManager ();

        static ResourceId loadNbar2File       (UI32 argc, vector<string> argv);

    protected :
    public :
        virtual                    ~PolicyObjectManager ();

        static PolicyObjectManager *getInstance         ();
        static string               getServiceName      ();
        static PrismServiceId       getPrismServiceId   ();

    // Now the data members

    private :
        CategoryWorker                          *m_pCategoryWorker;
        PolicyObjectManagerInitializationWorker *m_pPolicyObjectManagerInitializationWorker;
        ApplicationWorker                       *m_pApplicationWorker;

    protected :
    public :
};

}

#endif // POLICYOBJECTMANAGER_H

