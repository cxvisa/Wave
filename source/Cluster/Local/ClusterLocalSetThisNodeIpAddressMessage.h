/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CLUSTERLOCALSETTHISNODEIPADDRESSMESSAGE_H
#define CLUSTERLOCALSETTHISNODEIPADDRESSMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ClusterLocalSetThisNodeIpAddressMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                        ClusterLocalSetThisNodeIpAddressMessage ();
                        ClusterLocalSetThisNodeIpAddressMessage (const string &ipAddress);
        virtual        ~ClusterLocalSetThisNodeIpAddressMessage ();

                string  getIpAddress                            () const;
                void    setIpAddress                            (const string &ipAddress);

    // Now the data members

    private :
        string m_ipAddress;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSETTHISNODEIPADDRESSMESSAGE_H
