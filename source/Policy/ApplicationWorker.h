/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONWORKER_H
#define APPLICATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PolicyObjectManager;

class ApplicationWorker : public WaveWorker
{
    private :
                void               createCategory ();

        virtual WaveManagedObject *createManagedObjectInstance (const string &className);

    protected :
    public :
                 ApplicationWorker (PolicyObjectManager *pPolicyObjectManager);
        virtual ~ApplicationWorker ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // APPLICATIONWORKER_H

