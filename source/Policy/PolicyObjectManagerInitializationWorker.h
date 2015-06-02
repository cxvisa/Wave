/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef POLICYOBJECTMANAGERINITIALIZATIONWORKER_H
#define POLICYOBJECTMANAGERINITIALIZATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PolicyObjectManager;
class WaveAsynchronousContextForBootPhases;
class PolicyObjectManagerInitializationContext;

class PolicyObjectManagerInitializationWorker : public WaveWorker
{
    private :
        void install (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        void installLoadNbar2FileStep         (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installLoadPfrThresholdsFileStep (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installComputeCategoriesStep     (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installCreateCategoriesStep      (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installCreatePfrThresholdsStep   (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installCreateSubCategoriesStep   (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);
        void installCreateApplicationsStep    (PolicyObjectManagerInitializationContext *pPolicyObjectManagerInitializationContext);

    protected :
    public :
                 PolicyObjectManagerInitializationWorker (PolicyObjectManager *pPolicyObjectManager);
        virtual ~PolicyObjectManagerInitializationWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // POLICYOBJECTMANAGERINITIALIZATIONWORKER_H

