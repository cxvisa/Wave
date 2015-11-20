/*************************************************************************************************************************
 * Copyright (C) 2015-2015 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.LocationManagement;

import java.util.Set;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.Messaging.Remote.InterLocationMulticastMessage;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.SI32;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Socket.AcceptedStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Socket.ClientStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Socket.ServerStreamingSocket;
import com.CxWave.Wave.Framework.Utils.Synchronization.WaveMutex;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.LocationRole;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public abstract class LocationBase
{
    private WaveMutex               m_accessMutex;
    private WaveMutex               m_connectionEstablishmentMutex;

    protected LocationRole          m_locationRole             = LocationRole.LOCATION_STAND_ALONE;
    protected LocationId            m_locationId;
    protected String                m_ipAddress;
    protected String                m_ipAddressForHaInterface  = new String ("127.0.0.1");
    protected SI32                  m_port                     = new SI32 (0);
    protected SI32                  m_portForHaPeer            = new SI32 (0);

    protected LocationId            m_clusterPrimaryLocationId = new LocationId (0);
    protected SI32                  m_clusterPrimaryPort       = new SI32 (0);

    protected ServerStreamingSocket m_serverSocketForLocation  = null;
    protected ServerStreamingSocket m_serverSocketForHaPeer    = null;

    protected LocationBase (final LocationId locationId, final String ipAddress, final SI32 port)
    {
        m_locationId = locationId;
        m_ipAddress = ipAddress;
        m_port = port;
    }

    protected void lockAccess ()
    {
        m_accessMutex.lock ();
    }

    protected void unlockAccess ()
    {
        m_accessMutex.unlock ();
    }

    protected void setLocationId (final LocationId locationId)
    {
        m_locationId = locationId;
    }

    protected void lockConnectionEstablishment ()
    {
        m_connectionEstablishmentMutex.lock ();
    }

    protected void unlockConnectionEstablishment ()
    {
        m_connectionEstablishmentMutex.unlock ();
    }

    public abstract boolean supportsSubLocations ();

    public abstract void addSubLocation (final LocationId locationId, final String ipAddress, final SI32 port);

    ServerStreamingSocketStatus initializeServerCommunications ()
    {
        ServerStreamingSocketStatus status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND;

        if (null == m_serverSocketForLocation)
        {
            m_serverSocketForLocation = new ServerStreamingSocket (m_port);

            WaveAssertUtils.waveAssert (null != m_serverSocketForLocation);

            status = m_serverSocketForLocation.getStatus ();

            if (ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS != status)
            {
                m_serverSocketForLocation = null;
            }
        }
        else
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "LocationBase::initializeServerCommunications : Server Communications are already enabled for this location.");
        }

        return (status);
    }

    public abstract void initializeClientCommunications ();

    public ServerStreamingSocketStatus initializeHaPeerServerCommunications ()
    {
        ServerStreamingSocketStatus status = ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_ERROR_COULD_NOT_BIND;

        if (null == m_serverSocketForHaPeer)
        {
            m_serverSocketForHaPeer = new ServerStreamingSocket (m_portForHaPeer);

            WaveAssertUtils.waveAssert (null != m_serverSocketForHaPeer);

            status = m_serverSocketForHaPeer.getStatus ();

            if (ServerStreamingSocketStatus.SERVER_STREAMING_SOCKET_SUCCESS != status)
            {
                m_serverSocketForHaPeer = null;
            }
        }
        else
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_WARN, "LocationBase::initializeServerCommunications : Server Communications are already enabled for this Ha Peer.");
        }

        return (status);
    }

    public abstract ClientStreamingSocket getClientStreamingSocketForRemoteLocation (LocationId locationId);

    public abstract ClientStreamingSocket getClientStreamingSocketForHaPeer ();

    public abstract void invalidateClientStreamingSocketForRemoteLocation (LocationId locationId);

    public abstract void invalidateClientStreamingSocketForHaPeer ();

    public abstract ResourceId connectToRemoteLocation (final LocationId locationId, final UI32 numberOfRetries, final UI32 maximumNumberOfSecondsToTryFor);

    public abstract ResourceId connectToHaPeer (final String ipAddress, final SI32 port, final UI32 numberOfRetries, UI32 maximumNumberOfSecondsToTryFor);

    public abstract void addKnownLocation (final LocationId knownLocationId, final String ipAddress, final SI32 port);

    public abstract void removeKnownLocation (final LocationId knownLocationId);

    public LocationId getClusterPrimaryLocationId ()
    {
        return m_clusterPrimaryLocationId;
    }

    public void setClusterPrimaryLocationId (final LocationId clusterPrimaryLocationId)
    {
        m_clusterPrimaryLocationId = clusterPrimaryLocationId;
    }

    public SI32 getClusterPrimaryPort ()
    {
        return m_clusterPrimaryPort;
    }

    public void setClusterPrimaryPort (final SI32 clusterPrimaryPort)
    {
        m_clusterPrimaryPort = clusterPrimaryPort;
    }

    public ResourceId postToRemoteLocation (final String bufferToPost, final LocationId locationId)
    {
        lockAccess ();

        final ResourceId failureStatus = (!(getClusterPrimaryLocationId ().equals (locationId)) ? ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION : ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION_DUE_TO_PRINCIPAL_FAILOVER);
        final ClientStreamingSocket clientStreamingSocket = getClientStreamingSocketForRemoteLocation (locationId);

        if (null == clientStreamingSocket)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEVEL, new String ("LocationBase::postToRemoteLocation : We are not connected to this location to post the buffer: ") + locationId);

            unlockAccess ();

            return (failureStatus);
        }

        final int bufferSize = bufferToPost.length ();
        boolean isSuccessful = false;

        isSuccessful = clientStreamingSocket.send (bufferSize);

        if (true == isSuccessful)
        {
            isSuccessful = clientStreamingSocket.send (bufferToPost);
        }

        unlockAccess ();

        return (true == isSuccessful ? ResourceId.WAVE_MESSAGE_SUCCESS : failureStatus);
    }

    public ResourceId postToRemoteLocation (final InterLocationMulticastMessage interLocationMulticastMessage, final Set<LocationId> locationsToSend)
    {
        lockAccess ();

        final UI32 noOfLocationsToSent = new UI32 (locationsToSend.size ());
        final UI32 numberOfFailures = new UI32 (0);
        final String serializedStringToBeSent = interLocationMulticastMessage.getSerializedStringToSend ();

        interLocationMulticastMessage.messageOperationAccess ();

        final UI32 dataSize = new UI32 (serializedStringToBeSent.length ());
        final UI32 numberOfBuffers = new UI32 (0);

        for (final LocationId locationId : locationsToSend)
        {
            final ClientStreamingSocket clientStreamingSocket = getClientStreamingSocketForRemoteLocation (locationId);

            final ResourceId failureStatus = (((getClusterPrimaryLocationId ()).equals (locationId)) ? ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION : ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION_DUE_TO_PRINCIPAL_FAILOVER);

            if (null == clientStreamingSocket)
            {
                interLocationMulticastMessage.setStatusForALocation (locationId, failureStatus);
                interLocationMulticastMessage.setMessageRepliedToThisLocation (locationId);

                numberOfFailures.increment ();
                continue;
            }

            boolean isSuccessful = false;

            isSuccessful = clientStreamingSocket.send (dataSize);

            if (false == isSuccessful)
            {
                interLocationMulticastMessage.setStatusForALocation (locationId, failureStatus);
                interLocationMulticastMessage.setMessageRepliedToThisLocation (locationId);

                numberOfFailures.increment ();
            }
            else
            {
                isSuccessful = clientStreamingSocket.send (serializedStringToBeSent);

                if (false == isSuccessful)
                {
                    interLocationMulticastMessage.setStatusForALocation (locationId, failureStatus);
                    interLocationMulticastMessage.setMessageRepliedToThisLocation (locationId);

                    numberOfFailures.increment ();
                }
                else
                {
                    isSuccessful = clientStreamingSocket.send (numberOfBuffers);

                    if (false == isSuccessful)
                    {
                        interLocationMulticastMessage.setStatusForALocation (locationId, failureStatus);
                        interLocationMulticastMessage.setMessageRepliedToThisLocation (locationId);

                        numberOfFailures.increment ();
                    }
                    else
                    {
                        interLocationMulticastMessage.increment ();
                    }
                }
            }
        }

        interLocationMulticastMessage.messageOperationReleaseAccess ();

        unlockAccess ();

        return ((noOfLocationsToSent.equals (numberOfFailures)) ? ResourceId.WAVE_MESSAGE_ERROR : ResourceId.WAVE_MESSAGE_SUCCESS);
    }

    ResourceId postToRemoteLocation (final WaveMessage waveMessage, final LocationId locationId)
    {
        lockAccess ();

        final ResourceId failureStatus = ((getClusterPrimaryLocationId ()).equals (locationId)) ? ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION : ResourceId.WAVE_MESSAGE_ERROR_POST_TO_REMOTE_LOCATION_DUE_TO_PRINCIPAL_FAILOVER;

        final ClientStreamingSocket clientStreamingSocket = getClientStreamingSocketForRemoteLocation (locationId);

        boolean isSuccessful = false;

        if (null == clientStreamingSocket)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_DEVEL, new String ("LocationBase.postToRemoteLocation : We are not connected to this location to post the message: ") + locationId.toString ());

            unlockAccess ();

            return (failureStatus);
        }

        isSuccessful = clientStreamingSocket.send (waveMessage);

        unlockAccess ();

        return (true == isSuccessful ? ResourceId.WAVE_MESSAGE_SUCCESS : failureStatus);
    }

    public AcceptedStreamingSocket acceptNewConnection ()
    {
        AcceptedStreamingSocket acceptedStreamingSocket = null;

        if (null != m_serverSocketForLocation)
        {
            acceptedStreamingSocket = m_serverSocketForLocation.accept ();
        }
        else
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_ERROR, "LocationBase.acceptNewConnection : Server Communications are not initialized yet.");

            WaveAssertUtils.waveAssert ();
        }

        return (acceptedStreamingSocket);
    }
}
