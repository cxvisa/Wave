/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Regression.RegressionTestEntry;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerGetTestServiceEntriesMessage;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerRunTestForAServiceMessage;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;
import com.CxWave.Wave.Shell.Annotations.ShellSubordinate;

@ShellSubordinate (shell = ShellWave.class, token = "regression")
public class ShellRegression extends ShellBase
{
    private static Map<UI32, WaveServiceId> m_testServicesMap     = new HashMap<UI32, WaveServiceId> ();
    private static Map<UI32, Boolean>       m_testServiceStateMap = new HashMap<UI32, Boolean> ();

    private static ShellRegression          s_shellRegression     = null;

    public ShellRegression (final String name)
    {
        super (name);

        if (null == s_shellRegression)
        {
            s_shellRegression = this;
        }
        else
        {
            waveAssert ();
        }
    }

    @ShellCommand (shell = ShellRegression.class, briefHelp = "Lists all regression services available and their states.")
    public static void listServices (final Vector<String> arguments)
    {
        s_shellRegression.listServicesInternal (arguments);
    }

    private void listServicesInternal (final Vector<String> arguments)
    {
        final RegressionTestObjectManagerGetTestServiceEntriesMessage regressionTestObjectManagerGetTestServiceEntriesMessage = new RegressionTestObjectManagerGetTestServiceEntriesMessage ();

        final WaveMessageStatus sendStatus = sendSynchronously (regressionTestObjectManagerGetTestServiceEntriesMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
        {
            final ResourceId completionStatus = regressionTestObjectManagerGetTestServiceEntriesMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS == completionStatus)
            {
                final int numberOfRegressionTestServiceEntries = (regressionTestObjectManagerGetTestServiceEntriesMessage.getNumberOfTestServiceEntries ()).intValue ();
                int i = 0;

                for (i = 0; i < numberOfRegressionTestServiceEntries; i++)
                {
                    final RegressionTestEntry regressionTestEntry = regressionTestObjectManagerGetTestServiceEntriesMessage.getTestServiceEntryAt (new UI32 (i));

                    waveAssert (null != regressionTestEntry);

                    final WaveServiceId testServiceId = regressionTestEntry.getTestServiceId ();
                    final boolean testEnabled = regressionTestEntry.getIsTestEnabled ();
                    final String serviceName = FrameworkToolKit.getServiceNameById (testServiceId);
                    final String serviceState = testEnabled ? "Enabled" : "Disabled";

                    infoTracePrintf (false, true, "%3d - %-40s: %s\n", i, serviceName, serviceState);
                }
            }
            else
            {
                errorTracePrintf ("ShellRegression.listServices : Failed to fetch list of regression services.  Completion Status : %s", FrameworkToolKit.localize (completionStatus));
            }
        }
        else
        {
            errorTracePrintf ("ShellRegression.listServices : Failed to send a message to get list of regression services.  Send Status : %s", FrameworkToolKit.localize (sendStatus));
        }
    }

    public void populateServices ()
    {
        m_testServicesMap.clear ();
        m_testServiceStateMap.clear ();

        final RegressionTestObjectManagerGetTestServiceEntriesMessage regressionTestObjectManagerGetTestServiceEntriesMessage = new RegressionTestObjectManagerGetTestServiceEntriesMessage ();

        final WaveMessageStatus sendStatus = sendSynchronously (regressionTestObjectManagerGetTestServiceEntriesMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
        {
            final ResourceId completionStatus = regressionTestObjectManagerGetTestServiceEntriesMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS == completionStatus)
            {
                final int numberOfRegressionTestServiceEntries = (regressionTestObjectManagerGetTestServiceEntriesMessage.getNumberOfTestServiceEntries ()).intValue ();
                int i = 0;

                for (i = 0; i < numberOfRegressionTestServiceEntries; i++)
                {
                    final RegressionTestEntry regressionTestEntry = regressionTestObjectManagerGetTestServiceEntriesMessage.getTestServiceEntryAt (new UI32 (i));

                    waveAssert (null != regressionTestEntry);

                    final WaveServiceId testServiceId = regressionTestEntry.getTestServiceId ();
                    final boolean testEnabled = regressionTestEntry.getIsTestEnabled ();
                    final String serviceName = FrameworkToolKit.getServiceNameById (testServiceId);
                    final String serviceState = testEnabled ? "Enabled" : "Disabled";

                    infoTracePrintf (false, true, "%3d - %-40s: %s\n", i, serviceName, serviceState);

                    m_testServicesMap.put (new UI32 (i), testServiceId);
                    m_testServiceStateMap.put (new UI32 (i), testEnabled);
                }
            }
            else
            {
                errorTracePrintf ("ShellRegression.populateServices : Failed to fetch list of regression services.  Completion Status : %s", FrameworkToolKit.localize (completionStatus));
            }
        }
        else
        {
            errorTracePrintf ("ShellRegression.populateServices : Failed to send a message to get list of regression services.  Send Status : %s", FrameworkToolKit.localize (sendStatus));
        }
    }

    @ShellCommand (shell = ShellRegression.class, briefHelp = "Runs a Regression Test Service for a specified number of iterations.")
    public static void runTestService (final Vector<String> arguments)
    {
        s_shellRegression.runTestServiceInternal (arguments);
    }

    private void runTestServiceInternal (final Vector<String> arguments)
    {
        populateServices ();

        final int numberOfArguments = arguments.size ();

        if (0 > numberOfArguments)
        {
            errorTracePrintf ("ShellRegression.runTestServiceInternal : no test service index provided.");
            return;
        }

        final int index = Integer.parseInt (arguments.get (0));

        final UI32 testServiceIndex = new UI32 (index);

        int numberOfIterations = 1;

        if (2 <= numberOfArguments)
        {
            numberOfIterations = Integer.parseInt (arguments.get (1));
        }

        final WaveServiceId testServiceId = m_testServicesMap.get (testServiceIndex);
        final UI32 numberOfTimesToRunServiceTest = new UI32 (numberOfIterations);

        if (null == testServiceId)
        {
            errorTracePrintf ("ShellRegression.runTestServiceInternal : Invalid Test Service Index (%s).", testServiceIndex.toString ());
            return;
        }

        final RegressionTestObjectManagerRunTestForAServiceMessage regressionTestObjectManagerRunTestForAServiceMessage = new RegressionTestObjectManagerRunTestForAServiceMessage (testServiceId, numberOfTimesToRunServiceTest);

        final WaveMessageStatus sendStatus = sendSynchronously (regressionTestObjectManagerRunTestForAServiceMessage);

        if (WaveMessageStatus.WAVE_MESSAGE_SUCCESS == sendStatus)
        {
            final ResourceId completionStatus = regressionTestObjectManagerRunTestForAServiceMessage.getCompletionStatus ();

            if (ResourceId.WAVE_MESSAGE_SUCCESS == completionStatus)
            {

            }
            else
            {
                errorTracePrintf ("ShellRegression.runTestServiceInternal : Failed to fetch list of regression services.  Completion Status : %s", FrameworkToolKit.localize (completionStatus));
            }
        }
        else
        {
            errorTracePrintf ("ShellRegression.runTestServiceInternal : Failed to send a message to get list of regression services.  Send Status : %s", FrameworkToolKit.localize (sendStatus));
        }
    }
}
