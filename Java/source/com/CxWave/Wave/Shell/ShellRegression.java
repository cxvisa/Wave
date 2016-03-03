/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Shell;

import java.util.Vector;

import com.CxWave.Wave.Framework.ToolKits.Framework.FrameworkToolKit;
import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveServiceId;
import com.CxWave.Wave.Regression.RegressionTestEntry;
import com.CxWave.Wave.Regression.Messages.RegressionTestObjectManagerGetTestServiceEntriesMessage;
import com.CxWave.Wave.Resources.ResourceEnums.ResourceId;
import com.CxWave.Wave.Resources.ResourceEnums.WaveMessageStatus;
import com.CxWave.Wave.Shell.Annotations.ShellCommand;
import com.CxWave.Wave.Shell.Annotations.ShellSubordinate;

@ShellSubordinate (shell = ShellWave.class, token = "regression")
public class ShellRegression extends ShellBase
{
    private static ShellRegression s_shellRegression = null;

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

    @ShellCommand (shell = ShellRegression.class)
    public static void listServices (final Vector<String> arguments)
    {
        s_shellRegression.listServicesInternal (arguments);
    }

    public void listServicesInternal (final Vector<String> arguments)
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

                    infoTracePrintf ("%3d- %-40s: %s\n", i, serviceName, serviceState);
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
}
