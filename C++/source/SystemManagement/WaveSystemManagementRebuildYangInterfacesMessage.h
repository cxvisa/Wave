/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTREBUILDYANGINTERFACESMESSAGE_H
#define WAVESYSTEMMANAGEMENTREBUILDYANGINTERFACESMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementRebuildYangInterfacesMessage : public ManagementInterfaceMessage
{
    private :
    protected :
        virtual void setupAttributesForSerialization       ();
    public :
                        WaveSystemManagementRebuildYangInterfacesMessage ();
        virtual        ~WaveSystemManagementRebuildYangInterfacesMessage ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTREBUILDYANGINTERFACESMESSAGE_H 
