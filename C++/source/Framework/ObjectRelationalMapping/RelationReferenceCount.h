/**
 *@file RelationReferenceCount.h 
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

#ifndef RELATIONREFERENCECOUNT_H
#define RELATIONREFERENCECOUNT_H


#include "Framework/Types/Types.h"
namespace WaveNs
{

class RelationReferenceCount
{
  public:
    
  RelationReferenceCount ();
  virtual ~RelationReferenceCount ();
  void addReference ();   
  void removeReference ();
  virtual void processReferenceCreation ();
  virtual void processReferenceDeletion () ;   
  unsigned int getReferenceCount ();
  
  private:

  unsigned int mReferenceCount;

};

}
#endif //RELATIONREFERENCECOUNT_H

