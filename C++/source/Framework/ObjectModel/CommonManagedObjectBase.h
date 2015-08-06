/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Awanish Kumar Trivedi                                        *
 ***************************************************************************/

#ifndef COMMONMANAGEDOBJECTBASE_H
#define COMMONMANAGEDOBJECTBASE_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/PrismPersistableObject.h"
#include <string>

namespace WaveNs
{

class CommonManagedObjectBase 
{
    private :
    protected :
        virtual void                          setupAttributesForPersistence             ();
        virtual void                          setupAttributesForCreate                  ();

    public :
                                              CommonManagedObjectBase                         (PrismPersistableObject *pPrismPersistableObject);
        virtual                              ~CommonManagedObjectBase                         ();
        void                                  addPersistableAttributeForCommonBase            (Attribute *pAttribute);
        void                                  addPersistableAttributeForCommonBaseCreate      (Attribute *pAttribute);

    // Now the data members

    private :
    protected :
    public :
                PrismPersistableObject       *m_pPrismPersistableObject;

    private :
    protected :
    public :

};

}

#endif // COMMONMANAGEDOBJECTBASE_H
