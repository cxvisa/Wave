/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEOBJECTMANAGERTOOLKIT_H
#define WAVEOBJECTMANAGERTOOLKIT_H

#include "WaveResourceIdEnums.h"
#include "Framework/Types/Types.h"
#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/ObjectRelationalMapping/OrmRepository.h"
#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "Framework/ObjectModel/WaveElement.h"
#include <vector>
#include <string>

using namespace std;

namespace WaveNs
{

class WaveMessage;
class WaveManagedObjectSynchronousQueryContext;
class WaveManagedObject;
class ManagementInterfaceMessage;

class WaveObjectManagerToolKit
{
    private :
    protected :
    public :

    // Now the data members

    private :
    protected :
    public :
        static WaveMessageStatus            sendOneWay                      (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        static WaveMessageStatus            sendOneWayToFront               (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        static WaveMessageStatus            sendSynchronously               (WaveMessage *pWaveMessage, const LocationId &locationId = 0);
        static ResourceId                   sendSynchronouslyToWaveClient   (const string &waveClientName, ManagementInterfaceMessage *pManagementInterfaceMessage, const SI32 &Instnace = 0);
        static WaveMessageStatus            sendToWaveServer                (const UI32 &waveServerId, ManagementInterfaceMessage *pManagementInterfaceMessage, WaveMessageResponseHandler messageCallback, WaveElement *pWaveMessageSender, void *pInputContext, UI32 timeOutInMilliSeconds);
        static ResourceId                   sendOneWayToAllWaveClients      (ManagementInterfaceMessage *pManagementInterfaceMessage);

        static vector<WaveManagedObject *> *querySynchronously       (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext);
        static vector<WaveManagedObject *> *querySynchronously       (const string &managedClassName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        static vector<WaveManagedObject *> *querySynchronously       (const string &managedClassName, vector<ObjectId> &objectIds, const string &schema = OrmRepository::getWaveCurrentSchema ());
        static vector<WaveManagedObject *> *querySynchronouslyByName (const string &managedClassName, const string &managedObjectName, const string &schema = OrmRepository::getWaveCurrentSchema ());
        static vector<WaveManagedObject *> *querySynchronouslyLocalManagedObjectsForLocationId (const LocationId &locationId, const string &className);
        static WaveManagedObject           *queryManagedObject       (const ObjectId &managedObjectId, const string &schema = OrmRepository::getWaveCurrentSchema ());
        static ResourceId                   querySynchronouslyForCount (WaveManagedObjectSynchronousQueryContext *pWaveManagedObjectSynchronousQueryContext, UI32 &count);
        static ResourceId                   querySynchronouslyForCount (const string &managedClassName, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ());
        static ResourceId                   querySynchronouslyForCount (const string &managedClassName, const string &fieldName, const string &range, UI32 &count, const string &schema = OrmRepository::getWaveCurrentSchema ()); 
        static void                         getWaveConfigEntry         (string &configName, Attribute *attribute, bool &configFound);
};

}

#endif // WAVEOBJECTMANAGERTOOLKIT_H
