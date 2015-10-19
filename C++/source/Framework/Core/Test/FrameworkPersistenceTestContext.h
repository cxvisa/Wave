/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKPERSISTENCETESTCONTEXT_H
#define FRAMEWORKPERSISTENCETESTCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class WaveLinearSequencerContext;
class WaveTestManagedObject1;
class WaveTestManagedObject2;
class WaveTestManagedObject3;
class WaveTestManagedObject4;
class WaveTestManagedObject5;
class WaveTestManagedObject6;
class WaveTestManagedObject7;
class WaveTestManagedObject10;
class WaveTestManagedObject11;
class WaveTestManagedObject12;

class FrameworkPersistenceTestContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                                      FrameworkPersistenceTestContext  (WaveMessage *pWaveMessage, WaveElement *pWaveElement, WaveLinearSequencerStep *pSteps, UI32 numberOfSteps);
                                                     ~FrameworkPersistenceTestContext  ();

            vector<WaveTestManagedObject1 *>        &getCreatedObjects                 ();
            map<ObjectId, WaveTestManagedObject1 *> &getCreatedObjectsMap              ();
            vector<WaveTestManagedObject2 *>        &getCreatedObjects2                ();
            map<ObjectId, WaveTestManagedObject2 *> &getCreatedObjects2Map             ();
            vector<WaveTestManagedObject3 *>        &getCreatedObjects3                ();
            map<ObjectId, WaveTestManagedObject3 *> &getCreatedObjects3Map             ();
            vector<WaveTestManagedObject4 *>        &getCreatedObjects4                ();
            map<ObjectId, WaveTestManagedObject4 *> &getCreatedObjects4Map             ();
            vector<WaveTestManagedObject5 *>        &getCreatedObjects5                ();
            map<ObjectId, WaveTestManagedObject5 *> &getCreatedObjects5Map             ();
            vector<WaveTestManagedObject6 *>         &getCreatedObjects6                ();
            map<ObjectId, WaveTestManagedObject6 *>  &getCreatedObjects6Map             ();
            vector<WaveTestManagedObject7 *>         &getCreatedObjects7                ();
            map<ObjectId, WaveTestManagedObject7 *>  &getCreatedObjects7Map             ();
            vector<WaveTestManagedObject10 *>        &getCreatedObjects10               ();
            map<ObjectId, WaveTestManagedObject10 *> &getCreatedObjects10Map            ();
            vector<WaveTestManagedObject11 *>        &getCreatedObjects11               ();
            map<ObjectId, WaveTestManagedObject11 *> &getCreatedObjects11Map            ();
            vector<WaveTestManagedObject12 *>        &getCreatedObjects12               ();
            map<ObjectId, WaveTestManagedObject12 *> &getCreatedObjects12Map            ();

            UI32                                      getNumberOfObjectsToBeCreated     () const;
            void                                      setNumberOfObjectsToBeCreated     (const UI32 &numberOfObjectsToBeCtreated);

            UI32                                      getNumberOfObjectsForPartialQuery () const;
            void                                      setNumberOfObjectsForPartialQuery (const UI32 &numberOfObjectsForPartialQuery);

            UI32                                      getNumberOfExpectedResults        () const;
            void                                      setNumberOfExpectedResults        (const UI32 &numberOfExpectedResults);

    // Now the data members

    private :
        vector<WaveTestManagedObject1 *>        m_createdObjects;
        map<ObjectId, WaveTestManagedObject1 *> m_createdObjectsMap;
        vector<WaveTestManagedObject2 *>        m_createdObjects2;
        map<ObjectId, WaveTestManagedObject2 *> m_createdObjects2Map;
        vector<WaveTestManagedObject3 *>        m_createdObjects3;
        map<ObjectId, WaveTestManagedObject3 *> m_createdObjects3Map;
        vector<WaveTestManagedObject4 *>        m_createdObjects4;
        map<ObjectId, WaveTestManagedObject4 *> m_createdObjects4Map;
        vector<WaveTestManagedObject5 *>        m_createdObjects5;
        map<ObjectId, WaveTestManagedObject5 *> m_createdObjects5Map;
        vector<WaveTestManagedObject6 *>         m_createdObjects6;
        map<ObjectId, WaveTestManagedObject6 *>  m_createdObjects6Map;
        vector<WaveTestManagedObject7 *>         m_createdObjects7;
        map<ObjectId, WaveTestManagedObject7 *>  m_createdObjects7Map;
        vector<WaveTestManagedObject10 *>        m_createdObjects10;
        map<ObjectId, WaveTestManagedObject10 *> m_createdObjects10Map;
        vector<WaveTestManagedObject11 *>        m_createdObjects11;
        map<ObjectId, WaveTestManagedObject11 *> m_createdObjects11Map;
        vector<WaveTestManagedObject12 *>        m_createdObjects12;
        map<ObjectId, WaveTestManagedObject12 *> m_createdObjects12Map;

        UI32                                     m_numberOfObjectsToBeCreated;
        UI32                                     m_numberOfObjectsForPartialQuery;
        UI32                                     m_numberOfExpectedResults;

    protected :
    public :
};

}

#endif // FRAMEWORKPERSISTENCETESTCONTEXT_H
