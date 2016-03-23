/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.Core.Test;

import com.CxWave.Wave.Framework.Core.Wave;
import com.CxWave.Wave.Framework.Core.Configuration.WaveMainConfiguration;
import com.CxWave.Wave.Framework.ObjectModel.Annotations.ObjectManagerPriority;
import com.CxWave.Wave.Framework.ToolKits.Xml.XmlFile;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;
import com.CxWave.Wave.Framework.Utils.Configuration.WaveConfigurationFile;
import com.CxWave.Wave.Framework.Utils.Network.WaveNetworkUtils;
import com.CxWave.Wave.Framework.Utils.Sequencer.WaveLinearSequencerContext;
import com.CxWave.Wave.Framework.Utils.Trace.WaveTraceUtils;
import com.CxWave.Wave.Regression.WaveTestObjectManager;
import com.CxWave.Wave.Regression.Contexts.RegressionTestAsynchronousContext;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.TraceLevel;
import com.CxWave.Wave.Resources.ResourceEnums.WaveObjectManagerPriority;

@ObjectManagerPriority (WaveObjectManagerPriority.WAVE_OBJECT_MANAGER_PRIORITY_FRAMEWORK_CORE_TEST)
public class FrameworkCoreTestObjectManager extends WaveTestObjectManager
{
    private static FrameworkCoreTestObjectManager s_frameworkCoreTestObjectManager = null;

    public FrameworkCoreTestObjectManager ()
    {
        super (getServiceName ());
    }

    public static String getServiceName ()
    {
        return ("Framework Core Test");
    }

    public static FrameworkCoreTestObjectManager getInstance ()
    {
        if (null == s_frameworkCoreTestObjectManager)
        {
            s_frameworkCoreTestObjectManager = new FrameworkCoreTestObjectManager ();
        }

        WaveAssertUtils.waveAssert (null != s_frameworkCoreTestObjectManager);

        return (s_frameworkCoreTestObjectManager);
    }

    @Override
    public void handleTestRequest (final RegressionTestAsynchronousContext regressionTestAsynchronousContext)
    {
        develTracePrintf ("FrameworkCoreTestObjectManager.handleTestRequest : Entering ...");

        final String[] sequencerSteps =
            {
                            "basicsTestStep",
                            "waveLinearSequencerSucceededStep",
                            "waveLinearSequencerFailedStep"
            };

        final WaveLinearSequencerContext waveLinearSequencerContext = new WaveLinearSequencerContext (regressionTestAsynchronousContext, this, sequencerSteps);

        waveLinearSequencerContext.holdAll ();
        waveLinearSequencerContext.start ();
    }

    private void basicsTestStep (final WaveLinearSequencerContext waveLinearSequencerContext)
    {
        final String configurationFile = Wave.getWaveMainConfigurationFile ();

        final XmlFile xmlFile = new XmlFile (configurationFile);

        xmlFile.debugPrint ();

        final WaveConfigurationFile waveConfigurationFile = new WaveConfigurationFile (configurationFile);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "wave.application.name = %s", waveConfigurationFile.getConfigurationValue ("wave.application.name"));
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "wave.ras.trace.default-level = %s", waveConfigurationFile.getConfigurationValue ("wave.ras.trace.default-level"));

        final WaveMainConfiguration waveMainConfiguration1 = new WaveMainConfiguration ();

        waveMainConfiguration1.loadFromWaveConfigurationFile (configurationFile);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Application Name        : %s", (waveMainConfiguration1.getApplication ()).getApplicationName ());
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Application CompactName : %s", waveMainConfiguration1.getApplicationCompactName ());
        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Selected Ethernet Interface      : %s", (waveMainConfiguration1.getApplication ()).getEthernetInterface ());

        waveMainConfiguration1.debugPrint ();

        final StringBuffer stringBuffer = new StringBuffer ();

        waveMainConfiguration1.serializeTo (stringBuffer);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Serialized Data for WaveMain Configuration 1:\n%s", stringBuffer);

        final UI32 v1 = new UI32 (10);
        final UI32 v2 = new UI32 (10);
        final UI32 v3 = new UI32 (20);

        if (v1.equals (v2))
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 equals V2");
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 not equals V2");
        }

        if (v1.equals (v3))
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 equals V3");
        }
        else
        {
            WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "V1 not equals V3");
        }

        WaveMainConfiguration waveMainConfiguration2 = null;

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "loadFromSerializableObject Test (1000000 iterations) started.");

        for (int i = 0; i < 1000000; i++)
        {
            waveMainConfiguration2 = new WaveMainConfiguration ();
            waveMainConfiguration2.loadFromSerializableObject (waveMainConfiguration1);
        }

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "loadFromSerializableObject Test (1000000 iterations) End.");

        stringBuffer.delete (0, stringBuffer.length ());

        waveMainConfiguration2.serializeTo (stringBuffer);

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "Serialized Data for WaveMain Configuration 2:\n%s", stringBuffer);

        final WaveMainConfiguration wmc = waveMainConfiguration2;

        final String ethernetInterface = (wmc.getApplication ()).getEthernetInterface ();

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "A IPV4 Public Address for interface %s : %s", ethernetInterface, WaveNetworkUtils.getAIpV4PublicAddressForInterface (ethernetInterface));

        WaveTraceUtils.tracePrintf (TraceLevel.TRACE_LEVEL_INFO, "A IPV6 Public Address for interface %s : %s", ethernetInterface, WaveNetworkUtils.getAIpV6PublicAddressForInterface (ethernetInterface));

        waveLinearSequencerContext.executeNextStep (ResourceId.WAVE_MESSAGE_SUCCESS);
    }
}
