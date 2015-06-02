/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGATEWAYMESSAGE_H
#define WAVESYSTEMMANAGEMENTGATEWAYMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementGatewayMessage : public ManagementInterfaceMessage
{
    private :
    protected :
        virtual void setupAttributesForSerialization        ();
    public :
                        WaveSystemManagementGatewayMessage  ();
        virtual        ~WaveSystemManagementGatewayMessage  ();

        string          getWriteInputArguments              ();
        void            setWriteInputArguments              (string writeInputArguments);

        string          getWriteSubMode                     ();
        void            setWriteSubMode                     (string writeSubMode);

        void 			setCommandErrorString				(const string &clientStatus);
        string 			getCommandErrorString				() const;

        bool			getIsWyserEaCompatibilityMode() const;
        void 			setIsWyserEaCompatibilityMode(const bool &isWyserEaCompatibilityMode);


    // Now the data members

    private :
        string  m_writeInputArguments;
        string  m_writeSubMode;
        string  m_errorString;
        bool 	m_isWyserEaCompatibilityMode;
    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTREBUILDYANGINTERFACESMESSAGE_H 
