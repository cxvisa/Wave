/***********************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 ***********************************************************************************************************/

package com.CxWave.Wave.Framework.Type.AbstractDataType;

import java.util.LinkedList;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;

public class WavePriorityQueue<T extends Comparable<T>> extends LinkedList<T>
{
    private static final long serialVersionUID = 1L;

    WavePriorityQueue ()
    {
    }

    public void addElement (final T elementToBeInserted)
    {
        if (null == elementToBeInserted)
        {
            WaveTraceUtils.warnTracePrintf ("WavePriorityQueue.addElement : Null elements cannot be added.");

            return;
        }

        final int numberOfElements = size ();
        int searchBeginIndex = 0;
        int searchEndIndex = numberOfElements - 1;
        int insertionIndex = -1;
        int midPointIndex = 0;

        while (searchBeginIndex <= searchEndIndex)
        {
            midPointIndex = searchBeginIndex + (searchEndIndex / 2);

            final T existingElement = get (midPointIndex);

            WaveAssertUtils.waveAssert (null != existingElement);

            final int result = existingElement.compareTo (elementToBeInserted);

            if (0 == result)
            {
                insertionIndex = midPointIndex;
                break;
            }
            else if (-1 == result)
            {
                searchBeginIndex = midPointIndex + 1;
            }
            else
            {
                searchEndIndex = midPointIndex - 1;
            }
        }

        if (-1 == insertionIndex)
        {
            insertionIndex = searchBeginIndex;
        }

        add (insertionIndex, elementToBeInserted);
    }

    public T removeAndGetFirstElement ()
    {
        return (removeFirst ());
    }
}
