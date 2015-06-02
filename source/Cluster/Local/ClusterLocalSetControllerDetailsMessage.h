/**************************************************************************
*   Copyright (C) 2005-2014 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Himanshu Varshney                                            *
***************************************************************************/

#ifndef CLUSTERLOCALSETCONTROLLERDETAILSMESSAGE
#define CLUSTERLOCALSETCONTROLLERDETAILSMESSAGE
#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ClusterLocalSetControllerDetailsMessage : public ManagementInterfaceMessage
{
    private:
              void          setupAttributesForSerialization         (); 
    protected:
    public:
                            ClusterLocalSetControllerDetailsMessage (); 
              virtual      ~ClusterLocalSetControllerDetailsMessage (); 

              IpVxAddress   getControllerIpAddress                  ();
              void          setControllerIpAddress                  (const IpVxAddress &ipAddress);

              SI32          getControllerPort                       ();
              void          setControllerPort                       (const SI32 &port);
                
    //Data Members

    private:
              IpVxAddress   m_controllerIpAddress;
              SI32          m_controllerPort;
    protected:
    public:
    
};
 
}

#endif
