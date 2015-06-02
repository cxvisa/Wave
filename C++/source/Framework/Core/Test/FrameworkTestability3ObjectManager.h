/***************************************************************************
 *   Copyright (C) 2005-2006 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTESTABILITY3OBJECTMANAGER_H
#define FRAMEWORKTESTABILITY3OBJECTMANAGER_H

#include "Framework/ObjectModel/WaveObjectManager.h"

namespace WaveNs
{

class FrameworkTestabilityEvent1;

class FrameworkTestability3ObjectManager : public WaveObjectManager
{
    private :
                      FrameworkTestability3ObjectManager    ();
        PrismMessage *createMessageInstance                 (const UI32 &operationCode);

        void          listenForEvents                        (WaveAsynchronousContextForBootPhases *pWaveAsynchronousContextForBootPhases);

        void          frameworkTestabilityEvent1EventHandler (const FrameworkTestabilityEvent1 *&pEvent);

    protected :
    public :
        virtual                                    ~FrameworkTestability3ObjectManager     ();
        static  FrameworkTestability3ObjectManager *getInstance                            ();
        static  PrismServiceId                      getPrismServiceId                      ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FRAMEWORKTESTABILITY3OBJECTMANAGER_H
