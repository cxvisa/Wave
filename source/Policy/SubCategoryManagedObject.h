/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SUBCATEGORYMANAGEDOBJECT_H
#define SUBCATEGORYMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class PolicyObjectManager;

class SubCategoryManagedObject : public WaveManagedObject
{
    private :
        void setupAttributesForPersistence ();
        void setupAttributesForCreate      ();
        void setupKeys                     ();

    protected :
    public :
                          SubCategoryManagedObject        (PolicyObjectManager *pPolicyObjectManager);
        virtual          ~SubCategoryManagedObject        ();

        static  string    getClassName                    ();

                ObjectId  getPfrThresholdTemplateObjectId () const;
                void      setPfrThresholdTemplateObjectId (const ObjectId &pfrThresholdTemplateObjectId);

    // Now the data members

    private :
        ObjectId m_pfrThresholdTemplateObjectId;

    protected :
    public :
};

}

#endif // SUBCATEGORYMANAGEDOBJECT_H

