/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PFRTHRESHOLDMANAGEDOBJECT_H
#define PFRTHRESHOLDMANAGEDOBJECT_H

#include "Policy/PfrThresholdTemplateManagedObject.h"

namespace WaveNs
{

class PfrThresholdManagedObject : public PfrThresholdTemplateManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                        PfrThresholdManagedObject (PolicyObjectManager *pPolicyObjectManager);
        virtual        ~PfrThresholdManagedObject ();

        static  string  getClassName              ();

    // Now the data members

    private :
    protected :
    public :
};
}

#endif // PFRTHRESHOLDMANAGEDOBJECT_H
