/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERSAVEPRISMCONFIGURATIONMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERSAVEPRISMCONFIGURATIONMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

#include <string>

using namespace std;

namespace WaveNs
{

class PersistenceLocalObjectManagerSavePrismConfigurationMessage : public WaveMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        PersistenceLocalObjectManagerSavePrismConfigurationMessage  ();
                        PersistenceLocalObjectManagerSavePrismConfigurationMessage  (const bool &isStartupValid);
        virtual        ~PersistenceLocalObjectManagerSavePrismConfigurationMessage  ();

                bool    getIsStartupValid                                  () const;
                void    setIsStartupValid                                  (const bool &isStartupValid);

    // Now the data members

    private :
        bool      m_isStartupValid;

    protected :
    public :
};

}

#endif // PERSISTENCELOCALOBJECTMANAGERSAVEPRISMCONFIGURATIONMESSAGE_H
