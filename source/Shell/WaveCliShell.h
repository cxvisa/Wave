/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLISHELL
#define WAVECLISHELL

#include "Shell/WaveShell.h"
#include "ManagementInterface/ClientInterface/WaveClientSynchronousConnection.h"

namespace WaveNs
{

class WaveCliShell : public WaveShell
{
    private :
    protected :
                                         WaveCliShell  (WaveClientSynchronousConnection &connection);
                                         WaveCliShell  (const string &shellName, WaveClientSynchronousConnection &connection);

        WaveClientSynchronousConnection &getConnection ();

    public :
        virtual              ~WaveCliShell ();

        static  WaveCliShell *getInstance  (WaveClientSynchronousConnection &connection);

    // Now the data members

    private :
        WaveClientSynchronousConnection &m_connection;

    protected :
    public :
};

}

#endif // WAVECLISHELL
