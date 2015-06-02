/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

namespace WaveNs
{

typedef enum
{
    WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_QUALIFIED_YANG_PATH = 0,
    WAVE_SYSTEM_MANAGEMENT_GET_YANG_USER_INTERFACE                              = 1,
    WAVE_SYSTEM_MANAGEMENT_DISPLAY_CURRENT_CONFIGURATION_BY_TARGET_NODE_NAME    = 2,
    WAVE_SYSTEM_MANAGEMENT_REBUILD_YANG_INTERFACES                              = 3,
    WAVE_SYSTEM_MANAGEMENT_GET_POSSIBLE_COMPLETIONS_MESSAGE                     = 4,
    WAVE_SYSTEM_MANAGEMENT_GATEWAY_MESSAGE                                      = 5
} WaveSystemManagementTypes;

}
