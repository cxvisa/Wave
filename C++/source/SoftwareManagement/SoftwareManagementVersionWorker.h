/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SOFTWAREMANAGEMENTVERSIONWORKER_H
#define SOFTWAREMANAGEMENTVERSIONWORKER_H

#include "Framework/ObjectModel/WaveWorker.h"

namespace WaveNs
{

class SoftwareManagementObjectManager;
class SoftwareManagementGetVersionMessage;

class SoftwareManagementVersionWorker : public WaveWorker
{
    private :
        virtual WaveMessage *createMessageInstance                      (const UI32 &operationCode);

                void          softwareManagementGetVersionMessageHandler (SoftwareManagementGetVersionMessage *psoftwareManagementGetVersionMessage);
                void          getVersionStep                             (PrismLinearSequencerContext *pPrismLinearSequencerContext);

        static  void          debugGetVersion                            (UI32 argc, vector<string> argv);

    protected :
    public :
                 SoftwareManagementVersionWorker (SoftwareManagementObjectManager *pSoftwareManagementObjectManager);
        virtual ~SoftwareManagementVersionWorker ();

    // now the data members

    private :
    protected :
    public :
};

}

#endif // SOFTWAREMANAGEMENTVERSIONWORKER_H
