/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIENTSESSIONCONTEXT
#define WAVECLIENTSESSIONCONTEXT

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveClientSessionContext
{
    private :
    protected :
    public :
                    WaveClientSessionContext           ();
                    WaveClientSessionContext           (const LocationId &waveClientOriginatingLocationId, const UI32 &waveNativeClientId, const UI32 &waveUserClientId);
                   ~WaveClientSessionContext           ();

        void        setWaveClientOriginatingLocationId (const LocationId &waveClientOriginatingLocationId);
        LocationId  getWaveClientOriginatingLocationId () const;
        void        setWaveNativeClientId              (const UI32 &waveNativeClientId);
        UI32        getWaveNativeClientId              () const;
        void        setWaveUserClientId                (const UI32 &waveUserClientId);
        UI32        getWaveUserClientId                () const;

    // Now the data members

    private :
        LocationId m_waveClientOriginatingLocationId;
        UI32       m_waveNativeClientId;
        UI32       m_waveUserClientId;

    protected :
    public :
};

}

#endif // WAVECLIENTSESSIONCONTEXT

