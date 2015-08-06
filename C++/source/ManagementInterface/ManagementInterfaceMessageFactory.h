/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MANAGEMENTINTERFACEMESSAGEFACTORY_H
#define MANAGEMENTINTERFACEMESSAGEFACTORY_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class ManagementInterfaceMessageFactory
{
    private :
    protected :
    public :
        static ManagementInterfaceMessage *constructManagementInterfaceMessage (WaveServiceId serviceId, UI32 operationId);

    // NMow the data members

    private :
    protected :
    public :
};

}

#endif // MANAGEMENTINTERFACEMESSAGEFACTORY_H
