/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGENTRYMANAGEDOBJECT_H
#define DISTRIBUTEDLOGENTRYMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Attributes/AttributeDateTime.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

class DistributedLogObjectManager;

class DistributedLogEntryManagedObject : public WaveManagedObject
{
    private :
        void                    setupAttributesForPersistence    ();
        void                    setupAttributesForCreate         ();
        void                    setupKeys                        ();

    protected :
    public :
                                DistributedLogEntryManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager);
                                DistributedLogEntryManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager, const string &name);
        virtual                ~DistributedLogEntryManagedObject ();

        static  string          getClassName                     ();

                UI64            getLogId                         () const;
        void                    setLogId                         (const UI64 &logId);
                ResourceId      getLogType                       () const;
        void                    setLogType                       (const ResourceId &logType);
                ResourceId      getLogDescriptionType            () const;
        void                    setLogDescriptionType            (const ResourceId &logDescriptionType);
                DateTime        getDateTimeStamp                 () const;
        void                    setDateTimeStamp                 (const DateTime &dateTimeStamp);
                WaveServiceId  getWaveServiceId                () const;
        void                    setWaveServiceId                (const WaveServiceId &waveServiceId);
                string          getUsername                      () const;
        void                    setUsername                      (const string &username);
                string          getDescription                   () const;
        void                    setDescription                   (const string &description);
                ObjectId        getWaveNodeObjectId              () const;
        void                    setWaveNodeObjectId              (const ObjectId &waveNodeObjectId);
                ObjectId        getManagedObjectId               () const;
        void                    setManagedObjectId               (const ObjectId &managedObjectId);

    // Now the data members
    
    private :
                UI64            m_logId;
                ResourceId      m_logType;
                ResourceId      m_logDescriptionType;
                DateTime        m_dateTimeStamp;
                WaveServiceId  m_waveServiceId;
                string          m_username;
                string          m_description;
                ObjectId        m_waveNodeObjectId;
                ObjectId        m_managedObjectId;

    protected :
    public :
};

}

#endif // DISTRIBUTEDLOGENTRYMANAGEDOBJECT_H
