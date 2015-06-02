/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 **************************************************************************/

#ifndef UNIFIEDCLIENTCOMMON_H
#define UNIFIEDCLIENTCOMMON_H

#include <stdio.h>
#include <unistd.h>

#include "Framework/Types/WaveCValue.h"

enum UnifiedClientOpcode
{
    UNIFIEDCLIENTUPDATE = 370,
    UNIFIEDCLIENTCREATE,
    UNIFIEDCLIENTDELETE,
    UNIFIEDCLIENTPOSTBOOT,
    UNIFIEDCLIENTNOTIFY,       
    UNIFIEDCLIENTGETDATA
};

typedef struct UnifiedClientMessage
{
    int           groupCode;
    const char   *managedObjectName;
    const char  **attributeNames;
    const char  **parentManagedObjectNames;
    WaveCValue   *attributeValues;
    int           attributeSize;
    int           parentManagedObjectNamesSize;
    int           numberOfRecordsRequested; 
    int           isConfigReplayInProgress;
}UnifiedClientMessage_t;

typedef struct UnifiedClientBackendNotifyMessage
{
    int  backendNotifyValue;
} UnifiedClientNotifyMessage_t;

typedef struct UnifiedClientMessageInput
{
    int           groupCode;
    int           commandType;
    int           numberOfRecordsRequested;
    int           inputBufferSize;
    const void   *inputBuffer;
    int           commandStringSize; //argc in case of operational data
    const char  **commandString; //argv in case of operational data
}UnifiedClientMessageInput_t;

typedef struct UnifiedClientMessageOutput
{   
    int         moreRecords;
    int         bufferTag;
    int         outputBufferSize;
    const void *outputBuffer;
}UnifiedClientMessageOutput_t;

typedef struct UnifiedClientMessageOutputForConfig
{
    int           warningCode;
    const char  **attributeNames;
    const char  **attributeValues;
    int           attributeSize;
}UnifiedClientMessageOutputForConfig_t;


#endif
