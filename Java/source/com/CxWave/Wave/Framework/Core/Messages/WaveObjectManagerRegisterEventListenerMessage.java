
package com.CxWave.Wave.Framework.Core.Messages;

import com.CxWave.Wave.Framework.Messaging.Local.WaveMessage;
import com.CxWave.Wave.Framework.ObjectModel.FrameworkOpCodes;
import com.CxWave.Wave.Framework.Type.LocationId;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;

public class WaveObjectManagerRegisterEventListenerMessage extends WaveMessage
{
    private UI32          m_operationCodeToListenFor;
    private WaveServiceId m_listenerWaveServiceId;
    private LocationId    m_listenerLocationId;

    public WaveObjectManagerRegisterEventListenerMessage ()
    {
        super (WaveServiceId.NullServiceId, FrameworkOpCodes.WAVE_OBJECT_MANAGER_REGISTER_EVENT_LISTENER);
    }

    public WaveObjectManagerRegisterEventListenerMessage (final WaveServiceId serviceCode)
    {
        super (serviceCode, FrameworkOpCodes.WAVE_OBJECT_MANAGER_REGISTER_EVENT_LISTENER);
    }

    public WaveObjectManagerRegisterEventListenerMessage (final WaveServiceId serviceCode, final UI32 operationCodeToListenFor, final WaveServiceId listenerWaveServiceId, final LocationId listenerLocationId)
    {
        super (serviceCode, FrameworkOpCodes.WAVE_OBJECT_MANAGER_REGISTER_EVENT_LISTENER);

        m_operationCodeToListenFor = operationCodeToListenFor;
        m_listenerWaveServiceId = listenerWaveServiceId;
        m_listenerLocationId = listenerLocationId;
    }

    public UI32 getOperationCodeToListenFor ()
    {
        return m_operationCodeToListenFor;
    }

    public void setOperationCodeToListenFor (final UI32 operationCodeToListenFor)
    {
        m_operationCodeToListenFor = operationCodeToListenFor;
    }

    public WaveServiceId getListenerWaveServiceId ()
    {
        return m_listenerWaveServiceId;
    }

    public void setListenerWaveServiceId (final WaveServiceId listenerWaveServiceId)
    {
        m_listenerWaveServiceId = listenerWaveServiceId;
    }

    public LocationId getListenerLocationId ()
    {
        return m_listenerLocationId;
    }

    public void setListenerLocationId (final LocationId listenerLocationId)
    {
        m_listenerLocationId = listenerLocationId;
    }
}
