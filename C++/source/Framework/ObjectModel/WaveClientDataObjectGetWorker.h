/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                 *
 *   All rights reserved.                                                   *
 *   Author : Anil C                                                        *
 ***************************************************************************/

#ifndef WAVECLIENTDATAOBJECTGETWORKER_H
#define WAVECLIENTDATAOBJECTGETWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManagerGetDataFromClientMessage;
class WaveSendToClusterContext;
class WaveClientDataObjectGetWorker : public WaveWorker
{
    private :
                    WaveMessage       *createMessageInstance                   (const UI32 &operationCode);
                    void                getDataFromClientHandler                (WaveObjectManagerGetDataFromClientMessage *pWaveObjectManagerGetDataFromClientMessage);
                    void                getDataFromClientHandlerForSendToClient (WaveObjectManagerGetDataFromClientMessage *pWaveObjectManagerGetDataFromClientMessage)
;
                    void                getDataFromClientHandlerForSendToCluster(WaveObjectManagerGetDataFromClientMessage *pWaveObjectManagerGetDataFromClientMessage);

                    void                sendMessageToAllNodesStep               (WaveLinearSequencerContext *pWaveLinearSequencerContext);

                    void                sendMessageToAllNodesStepCallback       (WaveSendToClusterContext *pWaveSendToClusterContext);

    protected :
    public :
                                        WaveClientDataObjectGetWorker           (WaveObjectManager *pWaveObjectManger);
        virtual                        ~WaveClientDataObjectGetWorker           ();         

    //data members
    
    private :
    protected :
    public :
        
};

}

#endif //WAVECLIENTDATAOBJECTGETWORKER_H
