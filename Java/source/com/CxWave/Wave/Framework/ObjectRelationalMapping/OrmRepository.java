/*************************************************************************************************************************
 * Copyright (C) 2015-2016 Vidyasagara Guntaka & CxWave, Inc * All rights reserved. * Author : Vidyasagara Reddy Guntaka *
 *************************************************************************************************************************/

package com.CxWave.Wave.Framework.ObjectRelationalMapping;

import com.CxWave.Wave.Framework.Utils.Assert.WaveAssertUtils;

public class OrmRepository
{
    private static OrmRepository s_ormRepository = null;

    private OrmRepository ()
    {
    }

    public static OrmRepository getInstance ()
    {
        if (null == s_ormRepository)
        {
            s_ormRepository = new OrmRepository ();
        }

        WaveAssertUtils.waveAssert (null != s_ormRepository);

        return (s_ormRepository);
    }

    public void computeTableSpace ()
    {
    }
}
