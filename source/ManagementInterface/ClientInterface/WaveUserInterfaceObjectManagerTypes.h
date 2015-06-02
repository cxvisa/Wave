/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : acshetty                                                     *
 **************************************************************************/
#ifndef WAVEUSERINTERFACEOBJECTMANAGERTYPES_H
#define WAVEUSERINTERFACEOBJECTMANAGERTYPES_H


namespace WaveNs
{

// Unified Client Messages are also serviced by same OM 
// Make sure there is no overlap of opcodes. They can use from 370-410. Starting from 411 here.

typedef enum
{
   WAVE_UPDATE_CLIENT_STATUS = 411
}WaveUserInterfaceObjectManagerTypes;
}

#endif //WAVEUSERINTERFACEOBJECTMANAGERTYPES_H
