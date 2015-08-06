/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTPRIMARYNODECHANGEDMESSAGE_H
#define CLUSTERLOCALREPORTPRIMARYNODECHNAGEDMESSAGE_H

#include <string>
#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/WaveMessage.h"
namespace WaveNs
{

class WaveMessage;

///Class:
///ClusterLocalReportPrimaryNodeChangedMessage
/// 
///Description:
/// This Class represents the message that will be sent at the end of Phase2 
/// processing of an add or Rejoin to the Local Cluster Service so that
/// it can update its node status
 
class ClusterLocalReportPrimaryNodeChangedMessage: public  WaveMessage
{

    public :
        virtual        ~ClusterLocalReportPrimaryNodeChangedMessage ();
                        ClusterLocalReportPrimaryNodeChangedMessage ();
                        ClusterLocalReportPrimaryNodeChangedMessage (const string & thisNodeIpAddress,const UI32 thisNodePort,const LocationId   thisNodeLocationId);


                //Mutators
                void    setThisNodeIpAddress                         (const string &thisNodeName);
                void    setThisNodePort                              (const UI32 thisNodePort);
                void    setThisNodeLocationId                        (const LocationId thisLocationId);
       virtual  void    setupAttributesForSerialization              ();
 
                //Accessors
                string  const & getThisNodeIpAddress                 ()  const;
                UI32            getThisNodePort                      ()  const;
                LocationId      getThisNodeLocationId                ()  const;           

    protected :
    private :
    // Now the data members


    public:
    protected: 
    private :

        //This node info used in setting the fields in WaveNode
        string          m_thisNodeIpAddress;
        UI32            m_thisNodePort;
        UI32            m_thisNodeLocationId;

};


}

#endif // CLUSTERLOCALREPORTPRIMARYNODECHNAGEDMESSAGE_H
