/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Aashish Akhouri                                              *
 ***************************************************************************/

#ifndef CLUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERMESSAGE_H
#define CLUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERMESSAGE_H

#include <string>
#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"
namespace WaveNs
{

class PrismMessage;

///Class:
///ClusterLocalReportRemovedNodeFromClusterMessage
/// 
///Description:
/// This Class represents the message that will be sent at the beginning of 
/// unconfigure node processing from within the f/w on the secondary node. 
/// The ClusterLocalObject Manager will set the Local WaveNode to STAND_ALONE 
/// state.

class ClusterLocalReportRemovedNodeFromClusterMessage: public  PrismMessage
{

    public :
        virtual        ~ClusterLocalReportRemovedNodeFromClusterMessage ();
                        ClusterLocalReportRemovedNodeFromClusterMessage ();
                        ClusterLocalReportRemovedNodeFromClusterMessage (const string & ipAddresss,UI32 port,LocationId thisNodeLocationId);
                
                //Mutators
                void    setThisNodeIpAddress                         (const string &thisNodeName);
                void    setThisNodePort                              (UI32 thisNodePort);
                void    setThisNodeLocationId                        (LocationId thisLocationId);

        virtual void    setupAttributesForSerialization              (); 
 
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

#endif //CLUSTERLOCALREPORTREMOVEDNODEFROMCLUSTERMESSAGE_H

