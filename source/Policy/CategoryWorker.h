/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CATEGORYWORKER_H
#define CATEGORYWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PolicyObjectManager;

class CategoryWorker : public WaveWorker
{
    private :
        void createCategory ();

        virtual WaveManagedObject *createManagedObjectInstance (const string &className);

    protected :
    public :
                 CategoryWorker (PolicyObjectManager *pPolicyObjectManager);
        virtual ~CategoryWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CATEGORYWORKER_H

