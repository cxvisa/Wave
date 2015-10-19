/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef PERSISTENCETOOLKIT_H
#define PERSISTENCETOOLKIT_H

#include "Framework/Types/Types.h"
#include "Framework/Types/DateTime.h"
#include "Framework/Utils/WaveMutex.h"

using namespace std;

namespace WaveNs
{

class ConfigurationManagedObject;

class PersistenceToolKit
{
    private :
        static  void                        setConfigurationManagedObject                       (ConfigurationManagedObject* &pConfigurationManagedObject);
        static  ConfigurationManagedObject *getConfigurationManagedObject                       ();
        static  ResourceId                  getCachedConfigurationManagedObjectInformation      (UI64 &configurationTransactionId, DateTime &configurationTime, DateTime &latestUpdateTime);
        static  void                        clearConfigurationManagedObject                     ();

    protected :
    public :
        static  ResourceId                  getConfigurationManagedObjectInformation            (UI64 &configurationTransactionId, DateTime &configurationTime, DateTime &latestUpdateTime);
        static  ResourceId                  getConfigurationTransactionId                       (UI64 &configurationTransactionId);
        static  ResourceId                  getConfigurationTime                                (DateTime &configurationTime);
        static  ResourceId                  getLatestUpdateTime                                 (DateTime &latestUpdateTime);

    // Now the data members

    private :
        static  ConfigurationManagedObject *m_pConfigurationManagedObject;
        static  WaveMutex                  m_configurationManagedObjectMutex;

    protected :
    public :

    friend class PersistenceLocalObjectManager;
    friend class WaveFrameworkObjectManagerInitializeWorker;
};

}

#endif // PERSISTENCETOOLKIT_H
