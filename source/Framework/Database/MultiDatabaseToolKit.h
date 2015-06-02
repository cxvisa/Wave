/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef MULTIDATABASETOOLKIT_H
#define MULTIDATABASETOOLKIT_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class MultiDatabaseToolKit
{
    private :
    protected :
    public :
        static void addServerConnection          (const string &serverConnection);
        static void getServerConnections         (vector<string> &serverConnections);
        static void initializeServerConnections  (const string &serverConnectionString);
        static UI32 getNumberOfServerConnections ();
        static void getServerInformationAtIndex  (const UI32 &index, string &serverName, string &serverIpAddress, UI32 &serverPort);

        static bool getIsMultiModeEnabled        ();
        static void setIsMultiModeEnabled        (const bool &isMultiModeEnabled);

        // Now the data members

    private :
    protected :
    public :
        static vector<string> m_serverConnections;
        static vector<string> m_serverNames;
        static vector<string> m_serverIpAddresses;
        static vector<UI32>   m_serverPorts;
        static bool           m_isMultiModeEnabled;
};

}
#endif // MULTIDATABASETOOLKIT_H
