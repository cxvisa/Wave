/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : acshetty                                                     *
 ***************************************************************************/

#ifndef WAVEUSERINTERFACEOBJECTMANAGERMESSAGES_H
#define WAVEUSERINTERFACEOBJECTMANAGERMESSAGES_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveUpdateClientStatusMessage : public ManagementInterfaceMessage
{
    private :
    protected :

        virtual void setupAttributesForSerialization ();

    public :
                            WaveUpdateClientStatusMessage   ();
                            WaveUpdateClientStatusMessage   (const bool terminalMonitorStatus);
        virtual            ~WaveUpdateClientStatusMessage   ();

                      bool  getTerminalMonitorStatus        () const;
                      void  setTerminalMonitorStatus        (const bool &terminalMonitorStatus);

    // Now the data members

    private :
        bool m_terminalMonitorStatus;

    protected :
    public :
};

}

#endif // WAVEUSERINTERFACEOBJECTMANAGERMESSAGES_H
