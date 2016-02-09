/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.LocationManagement;

import java.util.Vector;

import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Socket.ClientStreamingSocket;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;

public class SubLocation extends LocationBase
{

    protected SubLocation (final LocationId locationId, final String ipAddress, final SI32 port)
    {
        super (locationId, ipAddress, port);
    }

    @Override
    public boolean supportsSubLocations ()
    {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void addSubLocation (final LocationId locationId, final String ipAddress, final SI32 port)
    {
        // TODO Auto-generated method stub

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
    public void addKnownLocation (final LocationId knownLocationId, final String ipAddress, final SI32 port)
    {
        // TODO Auto-generated method stub

    }

    @Override
    public void removeKnownLocation (final LocationId knownLocationId)
    {
        // TODO Auto-generated method stub

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

    @Override
    public void removeAllSubLocations ()
    {
        // TODO Auto-generated method stub

    }

    @Override
    public boolean isAKnownLocation (final LocationId locationId)
    {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public boolean isAConnectedLocation (final LocationId locationId)
    {
        // TODO Auto-generated method stub
        return false;
    }

}
