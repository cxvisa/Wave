/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTREPLACEMESSAGE_H
#define CLUSTERLOCALREPORTREPLACEMESSAGE_H

#include <string>
#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"
namespace WaveNs
{

class PrismMessage;

///Class:
///ClusterLocalReportReplaceMessage
/// 
///Description:
/// This Class represents the message that will be sent at the end of Phase2 
/// processing of an Replace Rejoin to the Local Cluster Service so that
/// it can update its node status
 
class ClusterLocalReportReplaceMessage: public  PrismMessage
{

    public :
        virtual        ~ClusterLocalReportReplaceMessage ();
                        ClusterLocalReportReplaceMessage ();
                        ClusterLocalReportReplaceMessage (const string & thisNodeIpAddress,const UI32 thisNodePort,const LocationId   thisNodeLocationId, const LocationId   replacedNodeLocationId);


                //Mutators
                void    setThisNodeIpAddress                         (const string &thisNodeName);
                void    setThisNodePort                              (const UI32 thisNodePort);
                void    setThisNodeLocationId                        (const LocationId thisLocationId);
                void    setReplacedNodeLocationId                    (const LocationId replacedLocationId);
       virtual  void    setupAttributesForSerialization              ();
 
                //Accessors
                string  const & getThisNodeIpAddress                 ()  const;
                UI32            getThisNodePort                      ()  const;
                LocationId      getThisNodeLocationId                ()  const;           
                LocationId      getReplacedNodeLocationId            ()  const;           

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
        UI32            m_replacedNodeLocationId;

};


}

#endif // CLUSTERLOCALREPORTREPLACEMESSAGE_H
