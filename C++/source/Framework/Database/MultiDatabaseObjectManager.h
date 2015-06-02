/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTIDATABASEOBJECTMANAGER_H
#define MULTIDATABASEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class WaveAsynchronousContextForBootPhases;
class DatabaseObjectManagerExecuteQueryWorker;
class DatabaseObjectManagerExecuteCursorCommandWorker;
class MultiDatabaseObjectManagerSetupServersWorker;

class MultiDatabaseObjectManager : public WaveLocalObjectManager
{

    private :
                     MultiDatabaseObjectManager ();
        virtual void boot                       (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

    protected :
    public :
        virtual                             ~MultiDatabaseObjectManager                ();

        static  MultiDatabaseObjectManager  *getInstance                               ();
        static  PrismServiceId               getPrismServiceId                         ();
        static  string                       getClassName                              ();

                WaveManagedObject           *loadWaveManagedObjectFromDatabase         (const ObjectId         &waveManagedObjectObjectId,  const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
                vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabase        (const vector<ObjectId> &waveManagedObjectObjectIds, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
                vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabase        (const string &childClassName, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
        static  WaveManagedObject           *loadWaveManagedObjectFromDatabaseWrapper  (const ObjectId         &waveManagedObjectObjectId,  const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
        static  vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabaseWrapper (const vector<ObjectId> &waveManagedObjectObjectIds, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);
        static  vector<WaveManagedObject *>  loadWaveManagedObjectsFromDatabaseWrapper (const string &childClassName, const ObjectId &parentObjectId, const string &schema, WaveObjectManager *pWaveObjectManager = NULL);


    // Now the data members

    private :
        DatabaseObjectManagerExecuteQueryWorker         *m_pDatabaseObjectManagerExecuteQueryWorker;
        DatabaseObjectManagerExecuteCursorCommandWorker *m_pDatabaseObjectManagerExecuteCursorCommandWorker;
        MultiDatabaseObjectManagerSetupServersWorker    *m_pMultiDatabaseObjectManagerSetupServersWorker;

    protected :
    public :

        friend class DatabaseObjectManager;
};

}

#endif // MULTIDATABASEOBJECTMANAGER_H
