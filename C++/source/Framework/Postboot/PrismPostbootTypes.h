/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTTYPES_H
#define PRISMPOSTBOOTTYPES_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{
typedef	struct  postbootTableEntry {
		string	passName;
		vector  <PrismServiceId> serviceId;
        vector  <int> recoveryType; // 1:1 mapping from serviceId and it's recoveryType. recoveryType is a bitmap to contain COLD, WARM, etc
} postbootPass;

}

#endif // PRISMPOSTBOOTAGENT_H
