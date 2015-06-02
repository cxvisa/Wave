/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jvenkata                                                     *
 **************************************************************************/

#ifndef HEARTBEATCONFIGLOCALMANAGEDOBJECT_H
#define HEARTBEATCONFIGLOCALMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveLocalManagedObject.h"

namespace WaveNs
{

    class HeartBeatObjectManager;
    class HeartBeatConfigLocalManagedObject : public WaveLocalManagedObject
    {
        private:
        protected:
            virtual void setupAttributesForPersistence();
            virtual void setupAttributesForCreate();
        public:
            HeartBeatConfigLocalManagedObject (HeartBeatObjectManager *pHeartBeatObjectManager);
            HeartBeatConfigLocalManagedObject (HeartBeatObjectManager *pHeartBeatObjectManager,const UI32 &defaultHeartBeatInterval,const UI32 &defaultHeartBeatFailureThreshold);
            virtual    ~HeartBeatConfigLocalManagedObject ();
            static string getClassName();
            void setDefaultHeartBeatInterval(const UI32 &defaultHeartBeatInterval);
            UI32 getDefaultHeartBeatInterval()  const;
            void setDefaultHeartBeatFailureThreshold(const UI32 &defaultHeartBeatFailureThreshold);
            UI32 getDefaultHeartBeatFailureThreshold()  const;

// Now the data members

        private:
        protected:
        public:
            UI32  m_defaultHeartBeatInterval;
            UI32  m_defaultHeartBeatFailureThreshold;
    };
}
#endif                                            //HEARTBEATCONFIGLOCALMANAGEDOBJECT_H
