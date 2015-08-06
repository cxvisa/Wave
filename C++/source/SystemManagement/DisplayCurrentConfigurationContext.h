/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef DISPLAYCURRENTCONFIGURATIONCONTEXT_H
#define DISPLAYCURRENTCONFIGURATIONCONTEXT_H

#include "Framework/Utils/WaveLinearSequencerContext.h"

namespace WaveNs
{

class YangDisplayConfigurationContext;
class YangElement;
class WaveManagedObjectQueryContext;

class DisplayCurrentConfigurationContext : public WaveLinearSequencerContext
{
    private :
    protected :
    public :
                                                 DisplayCurrentConfigurationContext  (WaveMessage *pWaveMessage, WaveElement *pWaveElement, PrismLinearSequencerStep *pSteps, UI32 numberOfSteps);
        virtual                                 ~DisplayCurrentConfigurationContext  ();

                YangDisplayConfigurationContext *getPYangDisplayConfigurationContext ();
                void                             setPYangDisplayConfigurationContext (YangDisplayConfigurationContext *pYangDisplayConfigurationContext);

                vector<YangElement *>            getYangElements                     ();
                void                             setYangElements                     (vector<YangElement *> &yangElements);

                UI32                             getCurrentYangElementIndex          () const;

                void                             advanceToNextYangElement            ();

                bool                             isAtTheLastYangElement              ();

                YangElement                     *getPYangElement                     ();
                void                             setPYangElement                     (YangElement *pYangElement);

                WaveManagedObjectQueryContext   *getPWaveManagedObjectQueryContext   ();
                void                             setPWaveManagedObjectQueryContext   (WaveManagedObjectQueryContext *pWaveManagedObjectQueryContext);

    // Now the data members

    private :
        YangDisplayConfigurationContext *m_pYangDisplayConfigurationContext;
        vector<YangElement *>            m_yangElements;
        UI32                             m_currentYangElementIndex;
        YangElement                     *m_pYangElement;
        WaveManagedObjectQueryContext   *m_pWaveManagedObjectQueryContext;

    protected :
    public :
};

}

#endif // DISPLAYCURRENTCONFIGURATIONCONTEXT_H
