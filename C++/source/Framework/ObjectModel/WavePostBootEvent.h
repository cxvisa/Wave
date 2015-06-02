/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu   			                                       *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTEVENT_H
#define	WAVEPOSTBOOTEVENT_H

namespace WaveNs
{

typedef enum
{
    POSTBOOT_EVENT_SERVICE_READY,
	POSTBOOT_EVENT_LINECARD_READY,
	POSTBOOT_EVENT_SYSTEM_READY

} PostbootEventTypes;

typedef enum
{
    POSTBOOT_GLOBAL_CONFIG,
    POSTBOOT_LINECARD_CONFIG

} PostbootConfigTypes;

}

#endif // WAVEPOSTBOOTEVENT_H

