/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef WAVEHANODE_H
#define WAVEHANODE_H

#include "Framework/ObjectModel/WaveLocalManagedObject.h"
#include "Cluster/Local/WaveHaNodeTypes.h"


namespace WaveNs
{

class WaveHaNode : public WaveLocalManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                            WaveHaNode      (WaveObjectManager *pWaveObjectManager);
                            WaveHaNode      (WaveObjectManager *pWaveObjectManager, const WaveHaNodeRole &role, const string &internalIpAddress, const string &seialNumber);
                            WaveHaNode      (WaveObjectManager *pWaveObjectManager, const WaveHaNodeRole &role);
                            WaveHaNode      (const WaveHaNode &waveNode);
        virtual            ~WaveHaNode      ();

        static  string      getClassName            ();

                WaveHaNodeRole  getHaRole           () const;
                void        setHaRole               (const WaveHaNodeRole &role);

                string      getInternalIpAddress    () const;
                void        setInternalIpAddress    (const string &ipAddress);

                string      getSerialNumber         () const;
                void        setSerialNumber         (const string &serialNumber);
    // now the data members

    private :
        WaveHaNodeRole      m_haRole;
        string              m_internalIpAddress;
        string              m_serialNumber;

    protected :
    public :
};

}

#endif // WAVEHANODE_H
