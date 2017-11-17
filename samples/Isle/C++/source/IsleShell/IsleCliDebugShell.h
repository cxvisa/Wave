/***************************************************************************
 *   Copyright (C) 2017 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef ISLECLIDEBUGSHELL_H
#define ISLECLIDEBUGSHELL_H

#include "Shell/WaveCliShell.h"
#include "IsleClientInterface/IsleClientSynchronousConnection.h"

using namespace WaveNs;

namespace IsleNs
{

class IsleCliDebugShell : public WaveCliShell
{
    private :
        void briefHelp ();

    protected :
    public :
                                                 IsleCliDebugShell                  (IsleClientSynchronousConnection &connection);
        virtual                                 ~IsleCliDebugShell                  ();

                IsleClientSynchronousConnection &getIsleClientSynchronousConnection ();

    // Now the data members

    private :
        IsleClientSynchronousConnection &m_isleClientSynchronousConnection;

    protected :
    public :
};

}

#endif // ISLECLIDEBUGSHELL_H
