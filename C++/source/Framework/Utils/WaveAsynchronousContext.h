/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 ***************************************************************************/

#ifndef WAVEASYNCHRONOUSCONTEXT_H
#define WAVEASYNCHRONOUSCONTEXT_H

#include "Framework/ObjectModel/WaveElement.h"

namespace WaveNs
{

class WaveAsynchronousContext;
class WaveManagedObject;

typedef void (WaveElement::* WaveAsynchronousCallback) (WaveAsynchronousContext *);

class WaveAsynchronousContext
{
    private :
                void                      garbageCollect     ();
    protected :
    public :
                                          WaveAsynchronousContext              (WaveElement *pCaller, WaveAsynchronousCallback pCallback, void *pCallerContext = NULL);
                                          WaveAsynchronousContext              (const WaveAsynchronousContext &waveAsynchronousContext);
        virtual                          ~WaveAsynchronousContext              ();
                WaveAsynchronousContext &operator =                            (const WaveAsynchronousContext &waveAsynchronousContext);
                void                      setCompletionStatus                   (const ResourceId &status);
                ResourceId                getCompletionStatus                   ();
                void                     *getPCallerContext                     ();

                void                      callback                              ();

                void                      addManagedObjectsForGarbageCollection (const vector<WaveManagedObject *> &managedObjectsForGarbageCollection);
                void                      addManagedObjectForGarbageCollection  (WaveManagedObject *pWaveManagedObjectForGarbageCollection);

    // Now the data members

    private :
        WaveElement              *      m_pCaller;
        WaveAsynchronousCallback        m_pCallback;
        void                      *const m_pCallerContext;
        ResourceId                       m_completionStatus;
        vector<WaveManagedObject *>      m_managedObjectsForGarbageCollection;

    protected :
    public :
};

}

#endif //WAVEASYNCHRONOUSCONTEXT_H
