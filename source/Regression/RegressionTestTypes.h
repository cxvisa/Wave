/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REGRESSIONTESTTYPES_H
#define REGRESSIONTESTTYPES_H

namespace WaveNs
{

typedef enum
{
    REGRESSION_GET_TEST_SERVICE_ENTRIES = 0,
    REGRESSION_SET_TEST_SERVICE_STATE,
    REGRESSION_START_REGRESSION,
    REGRESSION_PREPARE_TEST_FOR_A_SERVICE,
    REGRESSION_RUN_TEST_FOR_A_SERVICE
} RegresionMessageIds;

typedef enum
{
    REGRESSION_TEST_SUCCESS = 0, // FIXME : sagar : conver these enum values to Brocade Resources.
    REGRESSION_TEST_ERROR_INVALID_TEST_SERVICE_ID
} RegressionTestObjectManagerMessageStatus;

}

#endif // REGRESSIONTESTTYPES_H
