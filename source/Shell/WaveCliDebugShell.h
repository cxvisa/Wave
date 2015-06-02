/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIDEBUGSHELL_H
#define WAVECLIDEBUGSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliDebugShell : public WaveCliShell
{
    private :
                   WaveCliDebugShell                                        (WaveClientSynchronousConnection &connection);

        void       briefHelp                                                ();

        ResourceId testWaveManagementInterface                              (const vector<string> &arguments);
        void       testWaveManagementInterfaceHelp                          (void);

        ResourceId testDebugPrint                                           (const vector<string> &arguments);
        void       testDebugPrintHelp                                       (void);

        ResourceId testAsynchronousWaveManagementInterface                  (const vector<string> &arguments);

        ResourceId testAsynchronousMultipleResponseWaveManagementInterface  (const vector<string> &arguments);

        ResourceId testSendToWaveClientsManagementInterface                 (const vector<string> &arguments);

        ResourceId addLogEntry                                              (const vector<string> &arguments);

        ResourceId updateMaxLogEntries                                      (const vector<string> &arguments);

        void       debugPsql                                                (UI32 argc, vector<string> argv);
        void       debugPsqlHelp                                            (void);

        void       debugReleaseUnusedMemory                                 (UI32 argc, vector<string> argv);
        void       debugReleaseUnusedMemoryHelp                             (void);

        void       compareDBInCluster                                       (UI32 argc, vector<string> argv);
        void       compareDBInClusterHelp                                   (void);
        ResourceId messageHistoryDump                                       (const vector<string> &arguments);
        void       messageHistoryDumpHelp                                   (void);
        ResourceId messageHistoryConfig                                     (const vector<string> &arguments);
        void       messageHistoryConfigHelp                                 (void);

        ResourceId acquireLock                                              (const vector<string> &arguments);
        ResourceId releaseLock                                              (const vector<string> &arguments);
        
		ResourceId FIPSZeroize                                              (const vector<string> &arguments);

        ResourceId getDebugInformation                                      (const vector<string> &arguments);
        void       getDebugInformationHelp                                  (void);

        ResourceId resetDebugInformation                                    (const vector<string> &arguments);
        void       resetDebugInformationHelp                                (void);
        ResourceId runDebugScript                                           (const vector<string> &arguments);
		void       runDebugScriptHelp                                       (void);
        ResourceId setPrismConfigurationValid                               (const vector<string> &arguments);

        // Copy a file from this node to specified other nodes in the cluster.
        ResourceId copyFile                                                 (const vector<string> &arguments);
        void       copyFileHelp                                             (void);

        // Copy a file to Ha Peer (standby location.)
        ResourceId copyFileToHaPeer                                         (const vector<string> &arguments);
        void       copyFileToHaPeerHelp                                     (void);

        ResourceId printOrm                                                 (const vector<string> &arguments);
        void       printOrmHelp                                             (void); 

        ResourceId debugSchemaChange                                        (const vector<string> &arguments);
        void       debugSchemaChangeHelp                                    (void); 

        ResourceId addXPathStrings                                          (const vector<string> &arguments);
        void       addXPathStringsHelp                                      (void);

        ResourceId deleteXPathStrings                                       (const vector<string> &arguments);
        void       deleteXPathStringsHelp                                   (void);

        ResourceId getLastUpdateTimestampsForXPathStrings                   (const vector<string> &arguments);
        void       getLastUpdateTimestampsForXPathStringsHelp               (void);

        ResourceId resetLastUpdateTimestampsForXPathStrings                 (const vector<string> &arguments);
        void       resetLastUpdateTimestampsForXPathStringsHelp             (void);

        ResourceId debugChangeQuerySettings                                 (const vector<string> &arguments);
        void       debugChangeQuerySettingsHelp                             (void);

        ResourceId emptyDatabase                                            (const vector<string> &arguments);
        void       emptyDatabaseHelp                                        ();

        ResourceId getEmptyDatabaseParameter                                (const vector<string> &arguments);

        ResourceId changeEmptyDatabaseParameter                             (const vector<string> &arguments);
        void       changeEmptyDatabaseParameterHelp                         ();

        ResourceId setControllerIpAddress                                   (const vector<string> &arguments);

    protected :
    public :
        virtual ~WaveCliDebugShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLIDEBUGSHELL_H
