/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/
#ifndef FRAMEWORKTESTABILITY2OBJECTMANAGER_H
#define FRAMEWORKTESTABILITY2OBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"



namespace WaveNs
{

class FrameworkTestabilityEvent1;
class WaveNewNodesAddedEvent;
class WaveNodesAdditionToClusterCompletedEvent;
class WaveNodeLocalNodeDeletedEvent;
class PrimaryChangedEvent;
class StartupSchemaChangeEvent;

class FrameworkTestability2ObjectManager : public WaveLocalObjectManager
{
    private :
              FrameworkTestability2ObjectManager     ();

        void  listenForEvents                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        void  frameworkTestabilityEvent1EventHandler (const FrameworkTestabilityEvent1 *&pEvent);
        void WaveNewNodesAddedEventHandler           (const WaveNewNodesAddedEvent* & pEvent);
        void WaveNodesAdditionToClusterCompletedEventHandler(const WaveNodesAdditionToClusterCompletedEvent* & pEvent);
    	void WaveNodeLocalNodeDeletedEventHandler    (const WaveNodeLocalNodeDeletedEvent* & pEvent);
    	void PrimaryChangedEventHandler              (const PrimaryChangedEvent* & pEvent);
    	void StartupSchemaChangeEventHandler         (const StartupSchemaChangeEvent* & pEvent);

    protected :
    public :
        virtual                                    ~FrameworkTestability2ObjectManager ();
        static  FrameworkTestability2ObjectManager *getInstance                        ();
        static  WaveServiceId                      getWaveServiceId                  ();

    // Now the data members

     private :
     protected :
     public :
};

}

#endif // FRAMEWORKTESTABILITY2OBJECTMANAGER_H
