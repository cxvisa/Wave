/***************************************************************************
 *   Copyright (C) 2012-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERPUSHCONFIGTOKERNELMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERPUSHCONFIGTOKERNELMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerPushConfigToKernelMessaage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerPushConfigToKernelMessaage (const string &globalConfigs);
                        PersistenceLocalObjectManagerPushConfigToKernelMessaage ();
        virtual        ~PersistenceLocalObjectManagerPushConfigToKernelMessaage ();

                void    setGlobalConfigs                                        (const string &globalConfigs);
                string  getGlobalConfigs                                        () const;

    // Now the data members

    private :
        string m_globalConfigs;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERPUSHCONFIGTOKERNELMESSAGE_H
