/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Jayanth Venkataraman                                         *
 ***************************************************************************/

#ifndef FRAMEWORKTESTABILITY5OBJECTMANAGER_H
#define FRAMEWORKTESTABILITY5OBJECTMANAGER_H

#include "Framework/ObjectModel/WaveLocalObjectManager.h"

namespace WaveNs
{

class FrameworkTestabilityMessage10;

class FrameworkTestability5ObjectManager : public WaveLocalObjectManager
{
    private :
                            FrameworkTestability5ObjectManager     ();
        WaveMessage       *createMessageInstance                  (const UI32 &operationCode);
        WaveManagedObject  *createManagedObjectInstance            (const string &managedClassName);

        void                frameworkTestability10MessageHandler    (FrameworkTestabilityMessage10 *pMessage);

    protected :
    public :
        virtual                                    ~FrameworkTestability5ObjectManager     ();
        static  FrameworkTestability5ObjectManager *getInstance                            ();
        static  WaveServiceId                      getWaveServiceId                      ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FRAMEWORKTESTABILITY5OBJECTMANAGER_H
