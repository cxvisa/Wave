/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef POLICYOBJECTMANAGERTYPES_H
#define POLICYOBJECTMANAGERTYPES_H

typedef enum
{
    POLICY_OBJECT_MANAGER_CREATE_CATEGORY    = 0,
    POLICY_OBJECT_MANAGER_UPDATE_CATEGORY    = 1,
    POLICY_OBJECT_MANAGER_DELETE_CATEGORY    = 2,
    POLICY_OBJECT_MANAGER_CREATE_RELEVANCE   = 3,
    POLICY_OBJECT_MANAGER_UPDATE_RELEVANCE   = 4,
    POLICY_OBJECT_MANAGER_DELETE_RELEVANCE   = 5,
    POLICY_OBJECT_MANAGER_CREATE_APPLICATION = 6,
    POLICY_OBJECT_MANAGER_UPDATE_APPLICATION = 7,
    POLICY_OBJECT_MANAGER_DELETE_APPLICATION = 8,
    POLICY_OBJECT_MANAGER_CREATE_POLICY      = 9,
    POLICY_OBJECT_MANAGER_UPDATE_POLICY      = 10,
    POLICY_OBJECT_MANAGER_DELETE_POLICY      = 11
} PolicyObjectManagerTypes;

#endif // POLICYOBJECTMANAGERTYPES_H

