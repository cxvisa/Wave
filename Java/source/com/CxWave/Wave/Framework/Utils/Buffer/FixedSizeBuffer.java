/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Utils.Buffer;

import java.io.UnsupportedEncodingException;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;

public class FixedSizeBuffer
{
    private final UI32   m_maximumSize;
    private final byte[] m_rawBuffer;
    private UI32         m_currentSize;
    private boolean      m_isBufferOwnedByMe;

    public FixedSizeBuffer (final UI32 maximumSize)
    {
        m_maximumSize = maximumSize;
        m_isBufferOwnedByMe = true;

        if (0 == (m_maximumSize.getValue ()))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.FixedSizeBuffer : A FixedSizeBuffer of length 0 is not possible.");
            WaveAssertUtils.waveAssert ();
        }

        m_rawBuffer = new byte[(m_maximumSize.intValue ()) + 1];
        m_currentSize = new UI32 (0);

        if (null == m_rawBuffer)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.FixedSizeBuffer : Could not allocate a buffer.");
            WaveAssertUtils.waveAssert ();
        }

        m_rawBuffer[m_maximumSize.intValue ()] = '\0';
    }

    public FixedSizeBuffer (final UI32 maximumSize, final byte[] buffer, final boolean isBufferUsed)
    {
        m_maximumSize = maximumSize;
        m_isBufferOwnedByMe = false;

        if (0 == (m_maximumSize.getValue ()))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.FixedSizeBuffer : A FixedSizeBuffer of length 0 is not possible.");
            WaveAssertUtils.waveAssert ();
        }

        m_rawBuffer = buffer;

        if (true == isBufferUsed)
        {
            m_currentSize = m_maximumSize;
        }
        else
        {
            m_currentSize = new UI32 (0);
        }

        if (null == m_rawBuffer)
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.FixedSizeBuffer : Could not allocate a buffer.");
            WaveAssertUtils.waveAssert ();
        }
    }

    public byte[] getRawBuffer ()
    {
        return (m_rawBuffer);
    }

    public UI32 getMaximumSize ()
    {
        return (m_maximumSize);
    }

    public UI32 getCurrentSize ()
    {
        return (m_currentSize);
    }

    public UI32 getRemainingSize ()
    {
        if ((m_currentSize.getValue ()) > (m_maximumSize.getValue ()))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.getRemainingSize : Current size exceeded Maximum Size.  Something went wrong.");
            WaveAssertUtils.waveAssert ();
        }

        if ((m_currentSize.getValue ()) <= (m_maximumSize.getValue ()))
        {
            return (new UI32 ((m_maximumSize.getValue ()) - (m_currentSize.getValue ())));
        }
        else
        {
            return (new UI32 (0));
        }
    }

    public void incrementCurrentSize (final UI32 incrementSize)
    {
        final UI32 remainingSize = getRemainingSize ();

        if ((incrementSize.getValue ()) > (remainingSize.getValue ()))
        {
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_ERROR, "FixedSizeBuffer.incrementCurrentSize : Increment Size causes Current size to exceeded Maximum Size.  Something went wrong.");
            WaveTraceUtils.trace (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.incrementCurrentSize : Not incrementing the current size.");
            WaveAssertUtils.waveAssert ();
        }
        else
        {
            m_currentSize.increment (incrementSize);
        }
    }

    public boolean isFull ()
    {
        return (0 >= (getRemainingSize ()).getValue ());
    }

    @Override
    public String toString ()
    {
        String newString = null;

        try
        {
            newString = new String (m_rawBuffer, "UTF-8");
        }
        catch (final UnsupportedEncodingException e)
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_FATAL, "FixedSizeBuffer.toString : Unsupported Encoding : %s", "UTF-8");
            WaveAssertUtils.waveAssert ();
        }

        return (newString);
    }

    public void reset ()
    {
        m_currentSize = new UI32 (0);
    }

    public byte[] transferBufferToUser (final UI32 currentSize, final UI32 maximumSize)
    {
        if (false == m_isBufferOwnedByMe)
        {
            WaveAssertUtils.waveAssert ();
        }

        m_isBufferOwnedByMe = false;

        currentSize.setValue (m_currentSize.getValue ());
        maximumSize.setValue (m_maximumSize.getValue ());

        return (m_rawBuffer);
    }
}
