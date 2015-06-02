/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vipool Prajapati                                             *
 ***************************************************************************/

#ifndef CLUSTERREJOINCONTEXT_H
#define CLUSTERREJOINCONTEXT_H

#include "Framework/Utils/PrismLinearSequencerContext.h"
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class ClusterRejoinContext : public PrismLinearSequencerContext
{
    private:
    protected:
    public:
                                ClusterRejoinContext       (PrismMessage *pPrismMessage, PrismElement *pPrismElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                ~ClusterRejoinContext       (); 

                bool            getIsReplaceRejoin         () const;
                void            setIsReplaceRejoin         (const bool &isReplace);

    // Now the data members
    private:
                bool            m_isReplaceRejoin;

    protected:
    public:
};

}

#endif // CLUSTERREJOINCONTEXT_H
