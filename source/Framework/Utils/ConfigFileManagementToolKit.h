/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef CONFIGFILEMANAGEMENTTOOLKIT
#define CONFIGFILEMANAGEMENTTOOLKIT

#include "Framework/Types/Types.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class ConfigFileManagementToolKit
{
    private :
    protected :
    public :
        static      string                      getConfigFileManagementClientPath                       ();
        static      void                        setConfigFileManagementClientPath                       (const string &configFileManagementClientPath);

        static      string                      getConfigFileManagementConfigCmdPath                    ();
        static      void                        setConfigFileManagementConfigCmdPath                    (const string &configFileManagementConfigCmdPath);

        static      string                      getConfigFileManagementScriptsDirectory                 ();
        static      void                        setConfigFileManagementScriptsDirectory                 (const string &configFileManagementScriptsDirectory);

        static      string                      getConfigFileManagementDefaultClientEnvironmentSettings ();

        static      string                      getConfigFileManagementDefaultClientOptions             ();

        static      string                      getConfigFileManagementGlobalOnlyFilename               ();
        static      string                      getConfigFileManagementLocalOnlyFilename                ();

        static      SI32                        configFileManagementClientCommandOutput                 (const string &configFileManagementClientCommand, vector<string> &configFileManagementClientCommandOutput);
        static      SI32                        configFileManagementConfigCmdOutput                     (const string &configFileManagementConfigCmd, vector<string> &configFileManagementConfigCmdOutput);

        static      ResourceId                  copyRunningToStartup                                    ();
        static      ResourceId                  copyRunningToStartupFile                                ();

        static      bool                        isFileExisting                                          (const string &fullFilePath);

        static      ResourceId                  replayConfigurationFile                                 (const string &configFilePath, const string &configFilename, const string &preReplayActionCommands);
        static      ResourceId                  renameConfigurationFile                                 (const string &oldConfigFile, const string &newConfigFile);
        static      ResourceId                  deleteConfigurationFile                                 (const string &fullFilePath);
        static      void                        getDifference                                           (const vector<string> &set1, const vector<string> &set2, vector<string> &set1MinusSet2Difference);

       // Now the data members

    private :
    protected :
    public :
};

}

#endif // CONFIGFILEMANAGEMENTTOOLKIT
