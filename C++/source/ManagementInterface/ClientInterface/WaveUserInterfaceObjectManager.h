/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEUSERINTERFACEOBJECTMANAGER_H
#define WAVEUSERINTERFACEOBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class ManagementInterfaceMessage;
class WaveUpdateClientStatusMessage;

typedef ResourceId                  (*ManagementInterfaceMessageHandlerForClient)        (ManagementInterfaceMessage *pManagementInterfaceMessage);
typedef ManagementInterfaceMessage *(*ManagementInterfaceMessageInstantiatorForClient)   (const UI32 &operationCode);
typedef SI32                        (*ManagementInterfaceMessageHandlerForCStyleClient)  (const void *pInput, void ** const pOutput);

typedef void                        (*ManagementInterfaceMessageCallbackHandlerAtClient) (UI32 callbackStatus, const void *pOutput, void *pInputContext);
typedef void                       *(*ManagementClientInterfaceToLoadCStructureOutput)   (ManagementInterfaceMessage *pManagementInterfaceMessage);

class WaveUserInterfaceObjectManager : public WaveObjectManager
{
    private :
                                                                    WaveUserInterfaceObjectManager                          ();

        virtual PrismMessage                                       *createMessageInstance                                   (const UI32 &operationCode);

                void                                                genericManagementInterfaceMessageHandler                (ManagementInterfaceMessage *pManagementInterfaceMessage);
                void                                                genericManagementInterfaceMessageHandlerForCApplication (ManagementInterfaceMessage *pManagementInterfaceMessage);

                void                                                updateClientStatusFromServerMessageHandler              (WaveUpdateClientStatusMessage *pWaveUpdateClientStatusMessage);
                void                                                addMessageCallbackHandlerAtClient                       (UI32 messageId, ManagementInterfaceMessageCallbackHandlerAtClient messageCallback);
                ManagementInterfaceMessageCallbackHandlerAtClient   getMessageCallbackHandlerAtClient                       (const UI32 &messageId, const bool &isLastReply);              
    protected :
    public :
        virtual                                                  ~WaveUserInterfaceObjectManager                     ();

        static  WaveUserInterfaceObjectManager                   *getInstance                                        ();
        static  WaveServiceId                                    getWaveServiceId                                  ();
        static  string                                            getPrismServiceName                                ();

        static  void                                              setManagementInterfaceMessageHandlerForClient      (ManagementInterfaceMessageHandlerForClient managementInterfaceMessageHandlerForClient);
        static  void                                              setClientHandlerToLoadOutputForCStructure       (ManagementClientInterfaceToLoadCStructureOutput managementInterfaceMessageHandlerForClient);

        static  void                                              setManagementInterfaceMessageInstantiatorForClient (ManagementInterfaceMessageInstantiatorForClient managementInterfaceMessageInstantiatorForClient); // Client Side API
        static  void                                              setManagementInterfaceMessageInstantiatorForClient (const string &clientName, ManagementInterfaceMessageInstantiatorForClient managementInterfaceMessageInstantiatorForClient); // Server Side API
        static  ManagementInterfaceMessageInstantiatorForClient   getManagementInterfaceMessageInstantiatorForClient (const string &clientName);
        static  void                                              addMessageHandlerForCStyleApplication              (const UI32 &operationCode, ManagementInterfaceMessageHandlerForCStyleClient handler);
        static  ManagementInterfaceMessageHandlerForCStyleClient  getMessageHandlerForCStyleApplication              (const UI32 &operationCode);
                WaveMessageStatus                                 sendToWaveServer                                   (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, ManagementInterfaceMessageCallbackHandlerAtClient messageCallback, void *pInputContext = NULL, UI32 timeOutInMilliSeconds = 0, LocationId locationId = 0, PrismElement *pPrismMessageSender = NULL);
                void                                              sendToWaveServerCallback                           (FrameworkStatus frameworkStatus, ManagementInterfaceMessage *pManagementInterfaceMessage, void *pInputContext);
            	WaveMessageStatus                                 sendOneWayToWaveServer                             (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, const LocationId &locationId = 0);
                WaveMessageStatus                                 sendSynchronouslyToWaveServer                      (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, const LocationId &locationId = 0);
        static  void                                              replyToWaveServer                                  (ManagementInterfaceMessage *pManagementInterfaceMessage);
    // Now the Data Members
    private :
        static ManagementInterfaceMessageHandlerForClient                   m_managementInterfaceMessageHandlerForClient;
        static ManagementClientInterfaceToLoadCStructureOutput              m_managementClientInterfaceToLoadCStructureOuput;
        static ManagementInterfaceMessageInstantiatorForClient              m_managementInterfaceMessageInstantiatorForClient;
        static map<UI32, ManagementInterfaceMessageHandlerForCStyleClient>  m_managementInterfaceMessageHandlerMapForCStyleClient;
        static PrismMutex                                                   m_managementInterfaceMessageHandlerMapForCStyleClientMutex;
        static map<UI32, ManagementInterfaceMessageCallbackHandlerAtClient> m_managementInterfaceMessageCallbackHandlerAtCStyleClient;
        static PrismMutex                                                   m_managementInterfaceMessageCallbackHandlerAtCStyleClientMutex;
        static map<string, ManagementInterfaceMessageInstantiatorForClient> m_managementInterfaceMessageInstantiatorForClients;
        static PrismMutex                                                   m_managementInterfaceMessageInstantiatorForClientsMutex;
        static string                                                       m_ttyName;

    protected :
    public :

    friend void trace       (TraceLevel traceLevel, const string &stringToTrace);
    friend void tracePrintf (TraceLevel traceLevel, const bool &addNewLine, const bool &suppressPrefix, const char * const pFormat, ...);
    friend void tracePrintf (TraceLevel traceLevel, const char * const pFormat, ...);

};

}

#endif // WAVEUSERINTERFACEOBJECTMANAGER_H
