/**************************************************************************
*   Copyright (C) 2005-2014 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author : Himanshu Varshney                                            *
***************************************************************************/

#ifndef CLUSTERLOCALREPORTTOCONTROLLERASCLIENTMESSAGE
#define CLUSTERLOCALREPORTTOCONTROLLERASCLIENTMESSAGE
#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ClusterLocalReportToControllerAsClientMessage : public ManagementInterfaceMessage
{
    private:
              void          setupAttributesForSerialization ();
    protected:
    public:
                            ClusterLocalReportToControllerAsClientMessage ();
              virtual      ~ClusterLocalReportToControllerAsClientMessage ();

              IpVxAddress   getControllerIpAddress                        ();
              void          setControllerIpAddress                        (const IpVxAddress &ipAddress);

              SI32          getControllerPort                             ();
              void          setControllerPort                             (const SI32 &port);

              IpVxAddress   getControllerClientIpAddress                            ();
              void          setControllerClientIpAddress                            (const IpVxAddress &ipAddress);
          
              SI32          getControllerClientPort                       ();
              void          setControllerClientPort                       (const SI32 &port);

    //Data Members

    private:
              IpVxAddress   m_controllerIpAddress;
              SI32          m_controllerPort;
              IpVxAddress   m_controllerClientIpAddress;
              SI32          m_controllerClientPort;
    protected:
    public:
    
};
 
}


#endif

