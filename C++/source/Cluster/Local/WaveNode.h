/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVENODE_H
#define WAVENODE_H

#include "Framework/ObjectModel/WaveLocalManagedObject.h"
//#include "Cluster/Local/WaveSlotLocalManagedObject.h"
#include "Framework/ObjectModel/WaveManagedObjectPointer.h"


namespace WaveNs
{
class WaveSlotLocalManagedObject;
class WaveNode : public WaveLocalManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                            WaveNode                              (WaveObjectManager *pWaveObjectManager);
                            WaveNode                              (WaveObjectManager *pWaveObjectManager, const LocationId &locationId, const string &ipAddress, const UI32 &port);
                            WaveNode                              (const WaveNode &waveNode);
        virtual            ~WaveNode                              ();

        static  string      getClassName                          ();

                WaveNode   &operator =                            (const WaveNode &waveNode);
                bool        operator ==                           (const WaveNode &waveNode);
                bool        operator !=                           (const WaveNode &waveNode);

                LocationId  getLocationId                         () const;
                void        setLocationId                         (const LocationId &locationId);

                string      getIpAddress                          () const;
                void        setIpAddress                          (const string &ipAddress);

                UI32        getPort                               () const;
                void        setPort                               (const UI32 &port);

                ResourceId  getHardwareSynchronizationState       () const;
                void        setHardwareSynchronizationState       (ResourceId hardwareSynchronizationState);

                void        addWaveHaNode                         (const ObjectId &waveHaNodeObjectId);
                void        removeWaveHaNode                      (const ObjectId &secondaryNodeObjectId);
                void        removeAllHaNodes                      ();
				void		addWaveSlotLocalManagedObject		  (WaveSlotLocalManagedObject *pWaveSlotLocalManagedObject);
				void		removeWaveSlotLocalManagedObject	  (WaveSlotLocalManagedObject *pWaveSlotLocalManagedObject);
                void        removeAllWaveSlotLocalManagedObjects  ();

                IpVxAddress getContollerIpAddress                 () const;
                void        setContollerIpAddress                 (const IpVxAddress &ipAddress);

                UI32        getControllerPort                     () const;
                void        setControllerPort                     (const UI32 &port);

                ResourceId  getThisNodeStartMode                  ();
                void        setThisNodeStartMode                  (const ResourceId &startMode);
    // now the data members

    private :
        LocationId                                                    m_locationId;
        string                                                        m_ipAddress;
        UI32                                                          m_port;
        ResourceId                                                    m_hardwareSynchronizationState;
        vector<ObjectId>                                              m_waveHaNodes;
    	vector<WaveManagedObjectPointer<WaveSlotLocalManagedObject> > m_waveSlotLocalManagedObjects;
        IpVxAddress                                                   m_waveNodeControllerIpAddress;
        UI32                                                          m_waveNodeContollerPort;
        ResourceId                                                    m_waveNodeStartMode;

    protected :
    public :
};

}

#endif // WAVENODE_H
