
package com.CxWave.Wave.Regression;

import com.CxWave.Wave.Framework.Type.UI32;
import com.CxWave.Wave.Framework.Type.WaveOperationCodeInterface;

public enum RegressionMessageIds implements WaveOperationCodeInterface
{
    REGRESSION_GET_TEST_SERVICE_ENTRIES,
    REGRESSION_SET_TEST_SERVICE_STATE,
    REGRESSION_START_REGRESSION,
    REGRESSION_PREPARE_TEST_FOR_A_SERVICE,
    REGRESSION_RUN_TEST_FOR_A_SERVICE;

    private RegressionMessageIds ()
    {
    }

    @Override
    public UI32 getOperationCode ()
    {
        return (new UI32 (ordinal ()));
    }

    @Override
    public int getOperationCodeIntValue ()
    {
        return (ordinal ());
    }
}
