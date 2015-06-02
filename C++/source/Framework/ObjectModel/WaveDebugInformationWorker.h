/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVEDEBUGINFORMATIONWORKER_H
#define WAVEDEBUGINFORMATIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class WaveObjectManagerGetDebugInformationMessage;
class WaveObjectManagerResetDebugInformationMessage;
class WaveDebugInformationContext;
class WaveAsynchronousContextForDebugInformation;
class WaveObjectManager;

class WaveDebugInformationWorker : public WaveWorker
{
    private :
                PrismMessage   *createMessageInstance                           (const UI32 &operationCode);

                void            getDebugInformationHandler                      (WaveObjectManagerGetDebugInformationMessage *pWaveObjectManagerGetDebugInformationMessage);
                void            getDebugInformationWorkersStep                  (WaveDebugInformationContext *pWaveDebugInformationContext);
                void            getDebugInformationWorkersStepCallback          (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
                void            getDebugInformationObjectManagerStep            (WaveDebugInformationContext *pWaveDebugInformationContext);
                void            getDebugInformationObjectManagerStepCallback    (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

                void            resetDebugInformationHandler                    (WaveObjectManagerResetDebugInformationMessage *pWaveObjectManagerResetDebugInformationMessage);
                void            resetDebugInformationWorkersStep                (WaveDebugInformationContext *pWaveDebugInformationContext);
                void            resetDebugInformationWorkersStepCallback        (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);
                void            resetDebugInformationObjectManagerStep          (WaveDebugInformationContext *pWaveDebugInformationContext);
                void            resetDebugInformationObjectManagerStepCallback  (WaveAsynchronousContextForDebugInformation *pWaveAsynchronousContextForDebugInformation);

    protected :
    public :
                                WaveDebugInformationWorker                      (WaveObjectManager *pWaveObjectManger);
        virtual                ~WaveDebugInformationWorker                      ();

    // Now the data members

    private :
    protected :
    public :
};

}
#endif // WAVEDEBUGINFORMATIONWORKER_H

