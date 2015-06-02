/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.
 *   Himanshu Varshney 
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTASYNCHRONOUSCREATECONTEXT_H
#define WAVEMANAGEDOBJECTASYNCHRONOUSCREATECONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveManagedObjectAsynchronousCreateContext : public PrismAsynchronousContext
{
    private :
    protected :
    public :

                            WaveManagedObjectAsynchronousCreateContext  (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext);
        virtual            ~WaveManagedObjectAsynchronousCreateContext  ();

        vector<string>      getAttributeNames                           () const;
        void                setAttributeNames                           (const vector<string> &attributeNames);

        vector<string>      getAttributeValues                          () const;
        void                setAttributeValues                          (const vector<string> &attributeValues);
        
        string              getManagedObjectClassNameNeedToBeCreated    () const;
        void                setManagedObjectClassNameNeedToBeCreated    (const string &managedObjectClassName);

        ObjectId            getObjectId                                 () const;
        void                setObjectId                                 (const ObjectId &objectId);

        string              getParentAttributeName                      () const;
        void                setParentAttributeName                      (const string &attributeName);

    // Now the data members
    private :
        string              m_managedObjectClassName;
        ObjectId            m_objectId;
        vector<string>      m_attributeNames;
        vector<string>      m_attributeValues;
        string              m_parentAttributeName;

    protected :
    public :
};

}

#endif //WAVEMANAGEDOBJECTASYNCHRONOUSCREATECONTEXT_H
