/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEMESSAGE_H
#define WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementGetYangUserInterfaceMessage : public ManagementInterfaceMessage
{
    private :
    protected :
    public :
                        WaveSystemManagementGetYangUserInterfaceMessage ();
        virtual        ~WaveSystemManagementGetYangUserInterfaceMessage ();

                string &getYangUserInterface                            ();

    // Now the data members

    private :
        string m_yangUserInterface;

    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTGETYANGUSERINTERFACEMESSAGE_H
