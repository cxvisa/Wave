/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef DISTRIBUTEDLOGCONFIGURATIONMANAGEDOBJECT_H
#define DISTRIBUTEDLOGCONFIGURATIONMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"
#include "Framework/Attributes/Attributes.h"

namespace WaveNs
{

class DistributedLogObjectManager;

class DistributedLogConfigurationManagedObject : public WaveManagedObject
{
    private :
        void                setupAttributesForPersistence    ();
        void                setupAttributesForCreate         ();

    protected :
    public :
                            DistributedLogConfigurationManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager);
                            DistributedLogConfigurationManagedObject (DistributedLogObjectManager *pDistributedLogObjectManager, const string &name);
        virtual            ~DistributedLogConfigurationManagedObject ();

        static  string      getClassName                     ();
                UI64        getMaxLogEntries                 () const;
        void                setMaxLogEntries                 (const UI64 &logId);
                UI64        getFirstLogId                    () const;
        void                setFirstLogId                    (const UI64 &logId);
                UI64        getNextLogId                     () const;
        void                setNextLogId                     (const UI64 &logId);

    // Now the data members
    
    private :
        UI64        m_maxLogEntries;
        UI64        m_firstLogId;
        UI64        m_nextLogId;

    protected :
    public :
};

}

#endif // DISTRIBUTEDLOGCONFIGURATIONMANAGEDOBJECT_H
