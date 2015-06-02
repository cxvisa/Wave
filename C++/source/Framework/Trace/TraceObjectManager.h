/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef TRACEOBJECTMANAGER_H
#define TRACEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"
#include "Framework/Trace/TraceClientMap.h"
#include "Framework/ObjectModel/WaveAsynchronousContextForShutdownPhases.h"

#include <string>

namespace WaveNs
{

typedef void (*WaveUserClientPrintFunction)              (const UI32 &waveUserClientId, const string &messageToBePrinted);
typedef void (*WaveUserClientPrintToAllSessionsFunction) (const string &messageToBePrinted);

class TraceMessage;
class TraceObjectManagerSetClientTraceLevelMessage;
class TraceObjectManagerGetClientsInformationMessage;
class TraceObjectManagerPrintToAllWaveClientSessionsMessage;

class TraceObjectManager : public WaveLocalObjectManagerForUserSpecificTasks
{
    private :
                              TraceObjectManager                              ();
        virtual void          initialize                                      (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);
        virtual void          zeroize                                         (WaveAsynchronousContextForShutDownPhases *pWaveAsynchronousContextForShutDownPhases);
                void          traceMessageHandler                             (TraceMessage *pTraceMessage);
                void          setClientTraceLevelMessageHandler               (TraceObjectManagerSetClientTraceLevelMessage *pTraceObjectManagerSetClientTraceLevelMessage);
                void          getClientTraceLevelMessageHandler               (TraceObjectManagerGetClientTraceLevelMessage *pTraceObjectManagerGetClientTraceLevelMessage);
                void          getClientsInformationMessageHandler             (TraceObjectManagerGetClientsInformationMessage *pTraceObjectManagerGetClientsInformationMessage);
                void          printToWaveClientSessionMessageHandler          (TraceObjectManagerPrintToWaveClientSessionMessage *pTraceObjectManagerPrintToWaveClientSessionMessage);
                void          printToAllWaveClientSessionsMessageHandler      (TraceObjectManagerPrintToAllWaveClientSessionsMessage *pTraceObjectManagerPrintToAllWaveClientSessionsMessage);
                void          printToAllWaveDebugClientSessionsMessageHandler (TraceObjectManagerPrintToAllWaveDebugClientSessionsMessage *pTraceObjectManagerPrintToAllWaveDebugClientSessionsMessage);
                void          messageHistoryConfigForAServiceMessageHandler   (TraceObjectManagerMessageHistoryConfigForAServiceMessage *pMessageHistoryConfigForAServiceMessage);
                void          messageHistoryDumpForAServiceMessageHandler     (TraceObjectManagerMessageHistoryDumpForAServiceMessage *pMessageHistoryDumpForAServiceMessage);


        static  bool          getIsSysLogRequired                             ();
        static  void          setIsSysLogRequired                             (bool isSysLogRequired);

        virtual PrismMessage *createMessageInstance                      (const UI32 &operationCode);

        static  bool          isAKnownNativeClientDebugSession           (const UI32 &nativeClientId);
        static  bool          isAKnownUserClientDebugSession             (const UI32 &userClientId);
        static  void          printToAllDebugSessions                    (const string &messageToBePrinted);
        static  void          removeTraces                               (const string &filePath);
        static  string        getTraceTagForLevel                        (const TraceLevel& requestedTraceLevel);

    protected :
    public :
                                  ~TraceObjectManager                           ();
        static string              getClassName                                 ();
        static TraceObjectManager *getInstance                                  ();
        static PrismServiceId      getPrismServiceId                            ();
        static TraceClientId       addClient                                    (const TraceLevel &traceLevel, const string &traceClientName);
        static void                removeClient                                 (const string &traceClientName);
        static void                setTraceFileName                             (const string &traceFileName);
        static string              getTraceClientName                           (const TraceClientId &traceClientId);
        static bool                isTracingRequired                            (const TraceLevel &tracelevel, const TraceClientId &traceClientId);
        static void                traceDirectly                                (const TraceClientId &traceClientId, const TraceLevel &requestedTraceLevel, const string &stringToTrace, const bool &addNewLine, const bool &suppressPrefix);
        static void                traceDirectly                                (const TraceClientId &traceClientId, const TraceLevel &requestedTraceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, va_list &variableArguments);
        static void                traceDirectly                                (const TraceClientId &traceClientId, const TraceLevel &requestedTraceLevel, const char * const pFormat, va_list &variableArguments);
        static ResourceId          setClientTraceLevelDirectly                  (const TraceClientId &traceClientId, const TraceLevel &traceLevel, bool isSetAll = false);
        static TraceLevel          getClientTraceLevelDirectly                  (const TraceClientId &traceClientId);
        static void                getClientsInformationDirectly                (vector<TraceClientId> &traceClientIdsVector, vector<TraceLevel> &traceLevelsVector);

        static void                setPWaveUserClientPrintFunction              (WaveUserClientPrintFunction waveUserClientPrintFunction);
        static void                setPWaveUserClientPrintToAllSessionsFunction (WaveUserClientPrintToAllSessionsFunction waveUserClientPrintToAllSessionsFunction);

        static void                addNativeClientDebugSession                  (const UI32 &nativeClientId);
        static void                removeNativeClientDebugSession               (const UI32 &nativeClientId);
        static void                addUserClientDebugSession                    (const UI32 &userClientId);
        static void                removeUserClientDebugSession                 (const UI32 &userClientId);
        static UI32                getUserClientDebugSessionSize                ();
        static void                rotateTraceFile                              (bool noSizeCheck = false);

    // Now the data members

    private :
        static PrismMutex                               m_mutexForTracing;
        static bool                                     m_isFirstTime;
        static fstream                                  traceFile;

        static WaveUserClientPrintFunction              m_pWaveUserClientPrintFunction;
        static WaveUserClientPrintToAllSessionsFunction m_pWaveUserClientPrintToAllSessionsFunction;

        static map<UI32, UI32>                          m_nativeClientDebugSessions;
        static map<UI32, UI32>                          m_userClientDebugSessions;
        static PrismMutex                               m_clientDebugSessionsMutex;

        static UI32                                     m_maxTraceFileSize;
        static UI32                                     m_maxTraceFilesToKeep;
        static UI32                                     m_currentTraceFileSize;

    protected :
    public :

    friend class Wave;
    friend class WaveClient;
    friend class WaveCommandLineInterface;
    friend class WaveSystemManagement;
    friend class WaveMessageBroker;
    friend class WaveMessageBrokerClient;
};

}

#endif // TRACEOBJECTMANAGER_H
