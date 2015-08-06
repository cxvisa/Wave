/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef UPGRADEPERSISTENCETESTCONTEXT_H
#define UPGRADEPERSISTENCETESTCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class PrismLinearSequencerContext;
class UpgradeTestManagedObject1;
class UpgradeTestManagedObject2;
class UpgradeTestManagedObject3;
class UpgradeTestManagedObject4;
class UpgradeTestManagedObject5;
class UpgradeTestManagedObject6;
class UpgradeTestManagedObject7;

class UpgradePersistenceTestContext : public PrismLinearSequencerContext
{
private :
protected :
public :
    UpgradePersistenceTestContext  (WaveMessage *pWaveMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
    ~UpgradePersistenceTestContext  ();

    vector<UpgradeTestManagedObject1 *>        &getCreatedObjects                 ();
    map<ObjectId, UpgradeTestManagedObject1 *> &getCreatedObjectsMap              ();
    vector<UpgradeTestManagedObject2 *>        &getCreatedObjects2                ();
    map<ObjectId, UpgradeTestManagedObject2 *> &getCreatedObjects2Map             ();
    vector<UpgradeTestManagedObject3 *>        &getCreatedObjects3                ();
    map<ObjectId, UpgradeTestManagedObject3 *> &getCreatedObjects3Map             ();
    vector<UpgradeTestManagedObject4 *>        &getCreatedObjects4                ();
    map<ObjectId, UpgradeTestManagedObject4 *> &getCreatedObjects4Map             ();
    vector<UpgradeTestManagedObject5 *>        &getCreatedObjects5                ();
    map<ObjectId, UpgradeTestManagedObject5 *> &getCreatedObjects5Map             ();
    vector<UpgradeTestManagedObject6 *>         &getCreatedObjects6                ();
    map<ObjectId, UpgradeTestManagedObject6 *>  &getCreatedObjects6Map             ();
    vector<UpgradeTestManagedObject7 *>         &getCreatedObjects7                ();
    map<ObjectId, UpgradeTestManagedObject7 *>  &getCreatedObjects7Map             ();

    UI32                                      getNumberOfObjectsToBeCreated     () const;
    void                                      setNumberOfObjectsToBeCreated     (const UI32 &numberOfObjectsToBeCtreated);

    UI32                                      getNumberOfObjectsForPartialQuery () const;
    void                                      setNumberOfObjectsForPartialQuery (const UI32 &numberOfObjectsForPartialQuery);

    UI32                                      getNumberOfExpectedResults        () const;
    void                                      setNumberOfExpectedResults        (const UI32 &numberOfExpectedResults);

    // Now the data members

private :
    vector<UpgradeTestManagedObject1 *>        m_createdObjects;
    map<ObjectId, UpgradeTestManagedObject1 *> m_createdObjectsMap;
    vector<UpgradeTestManagedObject2 *>        m_createdObjects2;
    map<ObjectId, UpgradeTestManagedObject2 *> m_createdObjects2Map;
    vector<UpgradeTestManagedObject3 *>        m_createdObjects3;
    map<ObjectId, UpgradeTestManagedObject3 *> m_createdObjects3Map;
    vector<UpgradeTestManagedObject4 *>        m_createdObjects4;
    map<ObjectId, UpgradeTestManagedObject4 *> m_createdObjects4Map;
    vector<UpgradeTestManagedObject5 *>        m_createdObjects5;
    map<ObjectId, UpgradeTestManagedObject5 *> m_createdObjects5Map;
    vector<UpgradeTestManagedObject6 *>         m_createdObjects6;
    map<ObjectId, UpgradeTestManagedObject6 *>  m_createdObjects6Map;
    vector<UpgradeTestManagedObject7 *>         m_createdObjects7;
    map<ObjectId, UpgradeTestManagedObject7 *>  m_createdObjects7Map;

    UI32                                     m_numberOfObjectsToBeCreated;
    UI32                                     m_numberOfObjectsForPartialQuery;
    UI32                                     m_numberOfExpectedResults;

protected :
public :
};

}

#endif // UPGRADEPERSISTENCETESTCONTEXT_H
