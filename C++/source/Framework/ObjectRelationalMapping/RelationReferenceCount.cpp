/**
 *@file RelationReferenceCount.cpp
 * Copyright (C) 2011 Brocade Communications Systems,Inc.
 * All rights reserved. 
 * Description: This file has the implementation for the class
 *              that maintains the reference count of the
 *              relationships at the 'to' end of any
 *              relationship.If the refrencecount becomes 1 from
 *              0, then a call is made to an appropriate virtual
 *              function. Similary if teh reference count
 *              becomes 0 from 1 , then a call is made to the
 *              corresponding virtual function.
 *              
 *               
 * Author :     Aashish Akhouri 
 * Date :       11/04/2011 
 */

#include "Framework/ObjectRelationalMapping/RelationReferenceCount.h"

namespace WaveNs
{


RelationReferenceCount::RelationReferenceCount ()
:mReferenceCount(0)
{
}

RelationReferenceCount::~RelationReferenceCount ()
{
}

void RelationReferenceCount::addReference ()
{
  ++mReferenceCount;
  if(1==mReferenceCount) 
  {
      this->processReferenceCreation ();
  }
}

void RelationReferenceCount::removeReference ()
{
  --mReferenceCount;
  if(0==mReferenceCount) 
  {
      this->processReferenceDeletion ();
  }

}

void RelationReferenceCount::processReferenceCreation ()
{
  return;
}

void RelationReferenceCount::processReferenceDeletion ()
{

}
unsigned int RelationReferenceCount::getReferenceCount ()
{
  return mReferenceCount;
}
  
}
