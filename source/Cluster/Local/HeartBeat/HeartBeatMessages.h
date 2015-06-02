/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef HEARTBEATMESSAGES_H
#define HEARTBEATMESSAGES_H

#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"
#include "Cluster/Local/HeartBeat/HeartBeatTypes.h"


namespace WaveNs
{

class StartHeartBeatMessage : public PrismMessage
{
    private :
    protected :
                               StartHeartBeatMessage           (PrismServiceId serviceCode, UI32 operationCode);
                               StartHeartBeatMessage           (IpV4Address dstIpAddress, UI16 dstPortNumber);
                               StartHeartBeatMessage           (IpV4Address dstIpAddress, UI16 dstPortNumber, UI32 heartBeatInterval);
                               StartHeartBeatMessage           (IpV4Address dstIpAddress, UI16 dstPortNumber, UI32 heartBeatInterval, UI32 heartBeatFailureThreshold);
        virtual  void          setupAttributesForSerialization ();

    public :
        virtual               ~StartHeartBeatMessage           ();
                               StartHeartBeatMessage           ();
                 IpV4Address   getDstIpAddress                 ();
                 void          setDstIpAddress                 (IpV4Address dstIpAddress);
                 UI16          getDstPortNumber                ();
                 void          setDstPortNumber                (UI16 dstPortNumber);
                 UI32          getHeartBeatInterval            ();
                 void          setHeartBeatInterval            (UI32 heartBeatInterval);
                 UI32          getHeartBeatFailureThreshold    ();
                 void          setHeartBeatFailureThreshold    (UI32 heartbeatFailureThreshold);

    // Now the data members

    private :
    protected :
        IpV4Address     m_dstIpAddress;
        UI16            m_dstPortNumber;
        UI32            m_heartBeatInterval;
        UI32            m_heartBeatFailureThreshold;

    public :
};


class StopHeartBeatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
        virtual            ~StopHeartBeatMessage   ();
                            StopHeartBeatMessage   ();

    // Now the data members
    private :
    protected :
    public :
};

class PauseHeartBeatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
        virtual                            ~PauseHeartBeatMessage   ();
                                            PauseHeartBeatMessage   ();

    // Now the data members
    private :
    protected :
    public :
};

class ResumeHeartBeatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
        virtual                            ~ResumeHeartBeatMessage   ();
                                            ResumeHeartBeatMessage   ();

    // Now the data members

    private :
    protected :
    public :
};

class ConfigHeartBeatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
        virtual                            ~ConfigHeartBeatMessage   ();
                                            ConfigHeartBeatMessage   ();
    // Now the data members
    private :
    protected :
    public :
};

class GetHeartBeatStatMessage : public ManagementInterfaceMessage 
{
    private :
    protected :
        virtual  void                       setupAttributesForSerialization ();
    public :
        virtual                            ~GetHeartBeatStatMessage ();
                                            GetHeartBeatStatMessage ();
        IpV4Address                         getDstIpAddress         ();
        void                                setDstIpAddress         (IpV4Address dstIpAddress);
        UI16                                getDstPortNumber        ();
        void                                setDstPortNumber        (UI16 dstPortNumber);
    // Now the data members

    private :
    protected :
    public :
        IpV4Address               m_dstIpAddress;
        UI16                      m_dstPortNumber;
        UI32                      m_heartBeatSent;
        UI32                      m_heartBeatReplySent;
        
        UI32                      m_heartBeatReceived;
        UI32                      m_heartBeatReplyReceived;
        UI32                      m_lastHeartBeatReceived;
        UI32                      m_lastHeartBeatReplyReceived;
        
        UI32                      m_heartBeatLost;
        UI32                      m_heartBeatLostInRow;
        
        UI32                      m_heartBeatDelayed;
        UI32                      m_heartBeatDuplicate;


};

class ShowHeartBeatStatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
        virtual                            ~ShowHeartBeatStatMessage   ();
                                            ShowHeartBeatStatMessage   ();
    // Now the data members

    private :
    protected :
    public :
};

class ReportHeartBeatMessage : public StartHeartBeatMessage
{
    private :
    protected :
    public :
                void     setupAttributesForSerialization ();

        virtual         ~ReportHeartBeatMessage          ();
                         ReportHeartBeatMessage          ();
                
                UI32     getHeartBeatNum                 ();
                void     setHeartBeatNum                 (UI32 heartBeatNum);
            
                IpV4Address   getSenderIpAddress         ();
                void          setSenderIpAddress         (IpV4Address senderIpAddress);

                UI32     getSenderPort                   ();
                void     setSenderPort                   (UI32 senderPort);

    // Now the data members

    private :
        IpV4Address  m_senderIpAddress;
        UI32         m_senderPort;
        UI32         m_heartBeatNum;

    protected :
    public :
};

class DisconnectFromNodeMessage : public PrismMessage
{
 public:
  
                    DisconnectFromNodeMessage (LocationId locationId);
    virtual        ~DisconnectFromNodeMessage();

    //Accessors
    void            setLocationId       (LocationId locationId);
    void            setServerIpAddress  (const string &serverIpAddress);
    void            setServerPort       (const UI32   &serverPort);

    //Mutators
    LocationId      getLocationId       () const;
    string          getServerIpAddress  () const;
    UI32            getServerPort       () const;

 protected:
 private:



 public:
 protected:
 private:
    LocationId      mLocationId;
    string          m_serverIpAddress;
    UI32            m_serverPort;
};

}

#endif // HEARTBEATMESSAGES_H
