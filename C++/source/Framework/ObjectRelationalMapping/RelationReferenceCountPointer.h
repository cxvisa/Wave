/**
 *@file RelationReferenceCountPointer.h 
 * Copyright (C) 2011 Brocade Communications Systems,Inc.
 * All rights reserved. 
 * Description: This file declares the class that maintains the
 *              reference count of the relationships at the 'to'
 *              end of any relationship.
 *              
 *               
 * Author :     Aashish Akhouri 
 * Date :       11/04/2011 
 */


#ifndef RELATIONREFERENCECOUNTPOINTER_H
#define RELATIONREFERENCECOUNTPOINTER_H


#include "Framework/Types/Types.h"

namespace WaveNs
{

template<class T> class RelationReferenceCountPointer
{
 public:
  RelationReferenceCountPointer (const RelationReferenceCountPointer<T> & pRelationReferenceCountPointer);
  RelationReferenceCountPointer (T* pObjectPtr);
  ~RelationReferenceCountPointer ();
   T* get ();
  RelationReferenceCountPointer & operator=(RelationReferenceCountPointer & pRelationReferenceCountPointer);

  T*  operator->() const;
  T & operator*();
 private:
  T *mPtrToObject;

};




}


#endif
