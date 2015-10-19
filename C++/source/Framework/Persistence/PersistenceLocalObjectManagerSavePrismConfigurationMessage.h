/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERSAVEWAVECONFIGURATIONMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERSAVEWAVECONFIGURATIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerSaveWaveConfigurationMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerSaveWaveConfigurationMessage  ();
                        PersistenceLocalObjectManagerSaveWaveConfigurationMessage  (const bool &isStartupValid);
        virtual        ~PersistenceLocalObjectManagerSaveWaveConfigurationMessage  ();

                bool    getIsStartupValid                                  () const;
                void    setIsStartupValid                                  (const bool &isStartupValid);

    // Now the data members

    private :
        bool      m_isStartupValid;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERSAVEWAVECONFIGURATIONMESSAGE_H
