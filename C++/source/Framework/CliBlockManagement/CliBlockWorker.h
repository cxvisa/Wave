/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kuai Yu                                                      *
 ***************************************************************************/

#ifndef CLIBLOCKWORKER_H
#define CLIBLOCKWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"
#include "Framework/ObjectModel/WaveSendToClusterContext.h"

namespace WaveNs
{

class CentralClusterConfigObjectManager;
class CliBlockMessage;

class CliBlockWorker : public WaveWorker
{
    private :
        virtual PrismMessage *createMessageInstance                                            (const UI32 &operationCode);

                void          cliBlockMessageHandler                                           (CliBlockMessage *pCliBlockMessage);
                void          processCliBlockMessageForConnectedLocationStep                   (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void          processCliBlockMessageForConnectedLocationStepCallback           (WaveSendToClusterContext *pWaveSendToClusterContext);

    protected :
    public :
                 CliBlockWorker (CentralClusterConfigObjectManager *pCentralClusterConfigObjectManager);
        virtual ~CliBlockWorker ();

    // now the data members

    private :
    protected :
    public :
};

}

#endif // CLIBLOCKWORKER_H
