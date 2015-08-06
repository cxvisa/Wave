/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENCETESTOBJECTMANAGER_H
#define PERSISTENCETESTOBJECTMANAGER_H

#include "Regression/PrismTestObjectManager.h"
#include "Framework/Core/Test/FrameworkTestabilityMessages.h"

namespace WaveNs
{

class PrismLinearSequencerContext;
class RegressionTestMessage;

class PersistenceTestObjectManager : PrismTestObjectManager
{
    private :
                     PersistenceTestObjectManager           ();

        virtual void testRequestHandler                     (RegressionTestMessage *pRegressionTestMessage);
                void simpleTransactionForObjectCreationStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void nestedTransactionForObjectCreationStep (PrismLinearSequencerContext *pPrismLinearSequencerContext);
                void frameworkTestability9MessageCallback   (FrameworkStatus frameworkStatus, FrameworkTestabilityMessage9 *pMessage);

    protected :
    public :
                                            ~PersistenceTestObjectManager ();

        static PersistenceTestObjectManager *getInstance                  ();
        static WaveServiceId                getWaveServiceId            ();

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // PERSISTENCETESTOBJECTMANAGER_H
