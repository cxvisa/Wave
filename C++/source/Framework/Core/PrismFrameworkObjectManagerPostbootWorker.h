/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H
#define PRISMFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class PrismPostbootObjectManagerMessage;

class PrismFrameworkObjectManagerPostbootWorker : public WaveWorker
{
    private :
                void          postbootMessageHandler    (PrismPostbootObjectManagerMessage *pPrismPostbootObjectManagerMessage);

    protected :
    public :
                 PrismFrameworkObjectManagerPostbootWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~PrismFrameworkObjectManagerPostbootWorker ();

    // Now the Data Members
    private :
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H
