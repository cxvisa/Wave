/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTGATEWAYWORKER_H
#define WAVESYSTEMMANAGEMENTGATEWAYWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/Utils/PrismMutex.h"
#include "SystemManagement/WaveConfigurationSegmentWorker.h"

#include <map>

namespace WaveNs
{

class WaveSystemManagementGatewayMessage;
class YangElement;
class ObjectId;
class ConfigurationSegmentImportantInfo; 

class WaveSystemManagementGatewayWorker : public WaveWorker
{
    private:
    protected:
    public: 
                    WaveSystemManagementGatewayWorker   (WaveObjectManager *pWaveObjectManager);
                   ~WaveSystemManagementGatewayWorker   ();

    static  void            registerConfigurationSegment        (const string &configSegmentName, WaveConfigurationSegmentWorker *pWaveConfigurationSegmentWorker);

            void            gatewayMessageHandler               (WaveSystemManagementGatewayMessage *pWaveSystemManagementGatewayMessage);
    
            ResourceId      processWriteRequest                 (string inputArguments, string subMode, string &errorMessage, bool isWyserEaCompatibilityMode = false);
            
            ResourceId      sendManagementInterfaceMessage      (ManagementInterfaceMessage *pMessage, ConfigurationSegmentImportantInfo *pConfigurationSegmentImportantInfo, const LocationId &locationId = 0);

            YangElement    *getKeysAndAttributesForInput (const string &input, vector<string> &keyAttributeMoNames, vector<string> &keyAttributeNames, vector<string> &keyAttributeValues, vector<UI32> &keyAttributeUserTags, vector<YangElement *> &keyYangElement, string &targetNodeNameForData, YangElement *subModeTargetNodeName, bool isWyserEaCompatibilityMode = false);

            UI32            doesManagedObjectForKeyExist (const string &managedObjectName, vector<string> &keyAttributeMoNames, vector<string> &keyAttributeNames, vector<string> &keyAttributeValues, vector<UI32> &keyAttributeUserTags, string &targetNodeName, bool isSubModePresent, ObjectId parentObjectId, string &subModeTargetNodeName, bool isFirstCall);

            YangElement    *parseInputArguments (const string &targetNodeName, map<string, string> &listItemsInTargetNodeNameMap, vector<pair <string, string> > &leafItemsInTargetNodeNamePair, YangElement *subModeTargetYangElement, bool isWyserEaCompatibilityMode = false);

    static  void            addTargetNodeNameObjectIdMap        (const string &targetNodeName, ObjectId moObjectId);

    static  bool            deleteTargetNodeNameObjectIdMap     (const string &targetNodeName);

    static  ObjectId        getObjectIdForTargetNodeName        (const string &targetNodeName);

    static  bool            isTargetNodeNameInObjectIdMap       (const string &targetNodeName);

    static  UI32            deleteObjectIdsForBaseTargetNodeName        (const string &baseTargetNodeName);

    static  bool            clearTargetNodeNameObjectIdMap              ();
    static  void            printContentsOfTargetNodeNameObjectIdMap    ();

    // Data Members
    private:
        static map<string, ObjectId>   m_targetNodeNameObjectIdMap;
    protected:
    public:
            //static UI32 numberofqueries;
};

}

#endif
