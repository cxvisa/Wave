/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Regression.Messages;

import java.util.Vector;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.ManagementInterface.ClientInterface.ManagementInterfaceMessage;
import com.CxWave.Wave.Regression.RegressionMessageIds;
import com.CxWave.Wave.Regression.RegressionTestEntry;
import com.CxWave.Wave.Regression.RegressionTestObjectManager;

public class RegressionTestObjectManagerGetTestServiceEntriesMessage extends ManagementInterfaceMessage
{
    private final UI32                  m_numberOfTestServiceEntries = new UI32 (0);
    private final Vector<WaveServiceId> m_testServiceIds             = new Vector<WaveServiceId> ();
    private final Vector<Boolean>       m_testServiceStates          = new Vector<Boolean> ();

    public RegressionTestObjectManagerGetTestServiceEntriesMessage ()
    {
        super (RegressionTestObjectManager.getServiceName (), RegressionMessageIds.REGRESSION_GET_TEST_SERVICE_ENTRIES);
    }

    public void setNumberOfTestServiceEntries (final UI32 numberOfTestServiceEntries)
    {
        m_numberOfTestServiceEntries.setValue (numberOfTestServiceEntries);
    }

    public UI32 getNumberOfTestServiceEntries ()
    {
        return (m_numberOfTestServiceEntries);
    }

    public void addTestServiceEntry (final RegressionTestEntry regressionTestEntry)
    {
        m_testServiceIds.add (regressionTestEntry.getTestServiceId ());
        m_testServiceStates.add (regressionTestEntry.getIsTestEnabled ());
    }

    public RegressionTestEntry getTestServiceEntryAt (final UI32 index)
    {
        WaveAssertUtils.waveAssert ((m_testServiceIds.size ()) == (m_numberOfTestServiceEntries.getValue ()));

        WaveAssertUtils.waveAssert ((m_testServiceIds.size ()) == (m_testServiceStates.size ()));

        final int indexValue = (index.getValue ()).intValue ();

        if (indexValue < (m_testServiceIds.size ()))
        {
            return (new RegressionTestEntry (m_testServiceIds.get (indexValue), m_testServiceStates.get (indexValue)));
        }
        else
        {
            WaveTraceUtils.fatalTracePrintf ("RegressionTestObjectManagerGetTestServiceEntriesMessage.getTestServiceEntryAt : %s out of range %s", index.toString (), m_numberOfTestServiceEntries.toString ());

            WaveAssertUtils.waveAssert ();

            return (new RegressionTestEntry (new WaveServiceId (0), false));
        }
    }
}
