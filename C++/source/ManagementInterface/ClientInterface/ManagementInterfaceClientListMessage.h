/***************************************************************************
 *   Copyright (C) 2005 - 2013 Vidyasagara Guntaka                         *
 *   All rights reserved.                                                  *
 *   Author : Chaitanya Gangwar                                            * 
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACECLIENTLISTMESSAGE_H 
#define MANAGEMENTINTERFACECLIENTLISTMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ManagementInterfaceClientListMessage : public ManagementInterfaceMessage 
{
    private :
    protected :
        virtual void setupAttributesForSerialization ();

    public :
                                 ManagementInterfaceClientListMessage    ();
        virtual                 ~ManagementInterfaceClientListMessage    ();

                void             setConnectedClients                     (vector<string> connectedClients);
                vector<string>   getConnectedClients                     ();

    // Now the data members

    private :
    
        vector<string> m_connectedClients;
    
    protected :
    public :
};

}

#endif 
