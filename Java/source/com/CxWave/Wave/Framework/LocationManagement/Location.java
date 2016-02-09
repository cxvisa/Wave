/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.LocationManagement;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Socket.ClientStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.LocationRole;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class Location extends LocationBase
{
    private final Map<LocationId, SubLocation>           m_subLocations                   = new HashMap<LocationId, SubLocation> ();
    private final Map<LocationId, ClientStreamingSocket> m_clientSocketsForSubLocations   = new HashMap<LocationId, ClientStreamingSocket> ();

    private final Map<LocationId, Location>              m_knownLocations                 = new HashMap<LocationId, Location> ();
    private final Map<LocationId, ClientStreamingSocket> m_clientSocketsForKnownLocations = new HashMap<LocationId, ClientStreamingSocket> ();

    private final ClientStreamingSocket                  m_clientSocketForHaPeer          = new ClientStreamingSocket ();

    public Location (final LocationId locationId, final String ipAddress, final SI32 port)
    {
        super (locationId, ipAddress, port);

        setLocationRole (LocationRole.LOCATION_STAND_ALONE);
    }

    @Override
    public boolean supportsSubLocations ()
    {
        return (true);
    }

    @Override
    public void addSubLocation (final LocationId locationId, final String ipAddress, final SI32 port)
    {
        lockAccess ();

        if (m_subLocations.containsKey (locationId))
        {
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_subLocations.put (locationId, new SubLocation (locationId, ipAddress, port));
        }

        unlockAccess ();
    }

    @Override
    public void removeAllSubLocations ()
    {
        m_subLocations.clear ();

        m_clientSocketsForSubLocations.clear ();
    }

    @Override
    public void addKnownLocation (final LocationId knownLocationId, final String ipAddress, final SI32 port)
    {
        lockAccess ();

        if (m_knownLocations.containsKey (knownLocationId))
        {
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_knownLocations.put (knownLocationId, new Location (knownLocationId, ipAddress, port));
        }

        unlockAccess ();

    }

    @Override
    public void removeKnownLocation (final LocationId knownLocationId)
    {
        lockAccess ();

        if (m_knownLocations.containsKey (knownLocationId))
        {
            m_knownLocations.remove (knownLocationId);

            if (m_clientSocketsForKnownLocations.containsKey (knownLocationId))
            {
                final ClientStreamingSocket clientStreamingSocketForKnownLocation = m_clientSocketsForKnownLocations.get (knownLocationId);

                clientStreamingSocketForKnownLocation.close ();

                m_clientSocketsForKnownLocations.remove (knownLocationId);
            }
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_WARN, "The location : %s is already not known to us.", knownLocationId.toString ());

            // WaveAssertUtils.waveAssert ();
        }

        unlockAccess ();
    }

    @Override
    public boolean isAKnownLocation (final LocationId locationId)
    {
        lockAccess ();

        final boolean knownLocation = m_knownLocations.containsKey (locationId);

        unlockAccess ();

        return (knownLocation);
    }

    @Override
    public boolean isAConnectedLocation (final LocationId locationId)
    {
        lockAccess ();

        boolean knownLocation = m_knownLocations.containsKey (locationId);

        if (knownLocation)
        {
            if (null == (m_clientSocketsForKnownLocations.get (locationId)))
            {
                knownLocation = false;
            }
        }

        unlockAccess ();

        return (knownLocation);
    }

    @Override
    public void initializeClientCommunications ()
    {
        // TODO Auto-generated method stub

    }

    @Override
    public ClientStreamingSocket getClientStreamingSocketForRemoteLocation (final LocationId locationId)
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ClientStreamingSocket getClientStreamingSocketForHaPeer ()
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void invalidateClientStreamingSocketForRemoteLocation (final LocationId locationId)
    {
        // TODO Auto-generated method stub

    }

    @Override
    public void invalidateClientStreamingSocketForHaPeer ()
    {
        // TODO Auto-generated method stub

    }

    @Override
    public ResourceId connectToRemoteLocation (final LocationId locationId, final UI32 numberOfRetries, final UI32 maximumNumberOfSecondsToTryFor)
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public ResourceId connectToHaPeer (final String ipAddress, final SI32 port, final UI32 numberOfRetries, final UI32 maximumNumberOfSecondsToTryFor)
    {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public void resetLocationToStandAlone (final LocationId locationId)
    {
        // TODO Auto-generated method stub

    }

    @Override
    public void resetLocationToPrimary ()
    {
        // TODO Auto-generated method stub

    }

    @Override
    public void getFullyConnectedLocations (final Vector<LocationId> connectedLocationsVector)
    {
        // TODO Auto-generated method stub

    }

    @Override
    public void removeAllKnownLocations ()
    {
        // TODO Auto-generated method stub

    }
}
