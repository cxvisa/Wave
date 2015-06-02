/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef PRISMASYNCHRONOUSCONTEXT_H
#define PRISMASYNCHRONOUSCONTEXT_H

#include "Framework/ObjectModel/PrismElement.h"

namespace WaveNs
{

class PrismAsynchronousContext;
class WaveManagedObject;

typedef void (PrismElement::* PrismAsynchronousCallback) (PrismAsynchronousContext *);

class PrismAsynchronousContext
{
    private :
                void                      garbageCollect     ();
    protected :
    public :
                                          PrismAsynchronousContext              (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
                                          PrismAsynchronousContext              (const PrismAsynchronousContext &prismAsynchronousContext);
        virtual                          ~PrismAsynchronousContext              ();
                PrismAsynchronousContext &operator =                            (const PrismAsynchronousContext &prismAsynchronousContext);
                void                      setCompletionStatus                   (const ResourceId &status);
                ResourceId                getCompletionStatus                   ();
                void                     *getPCallerContext                     ();

                void                      callback                              ();

                void                      addManagedObjectsForGarbageCollection (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection);
                void                      addManagedObjectForGarbageCollection  (WaveManagedObject *pWaveManagedObjectForGarbageCollection);

    // Now the data members

    private :
        PrismElement              *      m_pCaller;
        PrismAsynchronousCallback        m_pCallback;
        void                      *const m_pCallerContext;
        ResourceId                       m_completionStatus;
        vector<WaveManagedObject *>      m_managedObjectsForGarbageCollection;

    protected :
    public :
};

}

#endif //PRISMASYNCHRONOUSCONTEXT_H
