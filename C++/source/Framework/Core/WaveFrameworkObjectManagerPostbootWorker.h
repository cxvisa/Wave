/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H
#define WAVEFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WavePostbootObjectManagerMessage;

class WaveFrameworkObjectManagerPostbootWorker : public WaveWorker
{
    private :
                void          postbootMessageHandler    (WavePostbootObjectManagerMessage *pWavePostbootObjectManagerMessage);

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

#endif // WAVEFRAMEWORKOBJECTMANAGERPOSTBOOTWORKER_H
