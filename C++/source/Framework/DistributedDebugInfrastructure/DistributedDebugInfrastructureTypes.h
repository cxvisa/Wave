 /*@file DistributedDebugInfrastructureTypes.h 
 * Copyright (C) 2011 BrocadeCommunications Systems,Inc.
 * All rights reserved.
 * Description: This file contains the declaration of all types
 *              used by the distributed debug infrastructure 
 *          
 *              
 * 
 * Author :     Aashish Akhouri 
 * Date :       06/18/2011 
 */
#ifndef DISTRIBUTEDDEBUGINFRASTRUCTURETYPES_H
#define DISTRIBUTEDDEBUGINFRASTRUCTURETYPES_H

namespace WaveNs
{

typedef enum
{
    RUN_DEBUG_SCRIPT_MESSAGE,
    RUN_DEBUG_SCRIPT_ON_CLUSTER_MEMBER_MESSAGE
} DistributedDebugInfrastructureTypes;

}

#endif // DISTRIBUTEDDEBUGINFRASTRUCTURETYPES_H
