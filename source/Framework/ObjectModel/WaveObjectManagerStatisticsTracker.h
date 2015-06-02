/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEOBJECTMANAGERSTATISTICSTRACKER_H
#define WAVEOBJECTMANAGERSTATISTICSTRACKER_H

#include "Framework/Types/Types.h"

#include <map>

namespace WaveNs
{

class WaveObjectManagerStatisticsTracker
{
    private :
    protected :
    public :
                                    WaveObjectManagerStatisticsTracker                  ();
        virtual                    ~WaveObjectManagerStatisticsTracker                  ();

                void                incrementManagedObjectsCreated                      (const string &managedObjectName);
                void                incrementManagedObjectsUpdated                      (const string &managedObjectName);
                void                incrementManagedObjectsDeleted                      (const string &managedObjectName);
                void                incrementCompositionsCreated                        (const string &compositionName);
                void                incrementCompositionsDeleted                        (const string &compositionName);
                void                incrementAssociationsCreated                        (const string &associationName);
                void                incrementAssociationsDeleted                        (const string &associationName);

                string              getManagedObjectsCreatedStatistics                  ();
                string              getManagedObjectsUpdatedStatistics                  ();
                string              getManagedObjectsDeletedStatistics                  ();
                string              getCompositionsCreatedStatistics                    ();
                string              getCompositionsDeletedStatistics                    ();
                string              getAssociationsCreatedStatistics                    ();
                string              getAssociationsDeletedStatistics                    ();

                string              getAllManagedObjectStatistics                       ();

                void                clearManagedObjectsCreatedMap                       ();
                void                clearManagedObjectsUpdatedMap                       ();
                void                clearManagedObjectsDeletedMap                       ();
                void                clearCompositionsCreatedMap                         ();
                void                clearCompositionsDeletedMap                         ();
                void                clearAssociationsCreatedMap                         ();
                void                clearAssociationsDeletedMap                         ();

                void                clearAllManagedObjectStatistics                     ();

    // Now the data members
    private :
                map<string, UI32>   m_managedObjectsCreated;
                map<string, UI32>   m_managedObjectsUpdated;
                map<string, UI32>   m_managedObjectsDeleted;
                map<string, UI32>   m_compositionsCreated;
                map<string, UI32>   m_compositionsDeleted;
                map<string, UI32>   m_associationsCreated;
                map<string, UI32>   m_associationsDeleted;

    protected :
    public :
};

}

#endif // WAVEOBJECTMANAGERSTATISTICSTRACKER_H
