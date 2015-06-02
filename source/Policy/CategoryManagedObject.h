/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CATEGORYMANAGEDOBJECT_H
#define CATEGORYMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class PolicyObjectManager;

class CategoryManagedObject : public WaveManagedObject
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();
        void setupKeys                     ();

    protected :
    public :
                        CategoryManagedObject (PolicyObjectManager *pPolicyObjectManager);
        virtual        ~CategoryManagedObject ();

        static  string  getClassName          ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // CATEGORYMANAGEDOBJECT_H

