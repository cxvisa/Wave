/**
 *@file RelationReferenceCountPointer.cpp 
 * Copyright (C) 2011 Brocade Communications Systems,Inc.
 * All rights reserved. 
 * Description: This file implements the class that maintains
 *              reference count of the relationships at the 'to'
 *              end of any relationship.
 *              
 *               
 * Author :     Aashish Akhouri 
 * Date :       11/04/2011 
 */

#include "Framework/ObjectRelationalMapping/RelationReferenceCountPointer.h"
namespace WaveNs
{


template<class T>  
RelationReferenceCountPointer<T>::RelationReferenceCountPointer (const RelationReferenceCountPointer<T> & pRelationReferenceCountPointer)
{
 
    mPtrToObject = pRelationReferenceCountPointer.get ();
    if(mPtrToObject)
    { 
     mPtrToObject->addReference ();
    }
}

template<class T>  
RelationReferenceCountPointer<T>::RelationReferenceCountPointer (T* ptrToObject)
{
 
  mPtrToObject = ptrToObject;
  if(ptrToObject)
  { 
   ptrToObject->addReference ();
  }
}

template<class T>  
RelationReferenceCountPointer<T>::~RelationReferenceCountPointer ()
{
  if(mPtrToObject)
  {
    mPtrToObject->removeReference ();
    mPtrToObject = 0;
  }  
 
}


template<class T>
T*  RelationReferenceCountPointer<T>::get () 
{
  return mPtrToObject;
}


template<class T>
RelationReferenceCountPointer<T> & RelationReferenceCountPointer<T>::operator=(RelationReferenceCountPointer & pRelationReferenceCountPointer)
{
  if(mPtrToObject)
  {
    mPtrToObject->removeReference ();
  }  
  
  mPtrToObject = pRelationReferenceCountPointer.get ();
 
  if(mPtrToObject)
  {
    mPtrToObject->addReference ();
  }
    
}

template<class T>
T*  RelationReferenceCountPointer<T>::operator-> ( ) const
{
  return mPtrToObject;

}


template<class T>
T &  RelationReferenceCountPointer<T>::operator* ()
{
  return *mPtrToObject;
}




}
