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

class WaveFrameworkObjectManagerPostbootWorker : public WaveWorker
{
    private :
                void          postbootMessageHandler    (PrismPostbootObjectManagerMessage *pPrismPostbootObjectManagerMessage);

    protected :
    public :
                 WaveFrameworkObjectManagerPostbootWorker (WaveObjectManager *pWaveObjectManager);
        virtual ~WaveFrameworkObjectManagerPostbootWorker ();

    // Now the Data Members
    private :
    protected :
    public :
};

}

#endif // PRISMFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H
