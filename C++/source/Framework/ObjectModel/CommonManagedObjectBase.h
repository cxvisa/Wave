/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Awanish Kumar Trivedi                                        *
 ***************************************************************************/

#ifndef COMMONMANAGEDOBJECTBASE_H
#define COMMONMANAGEDOBJECTBASE_H

#include "Framework/ObjectModel/WaveElement.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/ObjectModel/WavePersistableObject.h"
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
                                              CommonManagedObjectBase                         (WavePersistableObject *pWavePersistableObject);
        virtual                              ~CommonManagedObjectBase                         ();
        void                                  addPersistableAttributeForCommonBase            (Attribute *pAttribute);
        void                                  addPersistableAttributeForCommonBaseCreate      (Attribute *pAttribute);

    // Now the data members

    private :
    protected :
    public :
                WavePersistableObject       *m_pWavePersistableObject;

    private :
    protected :
    public :

};

}

#endif // COMMONMANAGEDOBJECTBASE_H
