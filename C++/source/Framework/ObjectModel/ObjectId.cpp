/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Utils/StringUtils.h"

namespace WaveNs
{

ObjectId ObjectId::NullObjectId;

ObjectId::ObjectId (UI32 classId, UI64 instanceId)
    : m_classId (classId),
      m_instanceId (instanceId)
{
}

ObjectId::ObjectId (const ObjectId &rhs)
    : m_classId (rhs.m_classId),
      m_instanceId (rhs.m_instanceId)
{
}

ObjectId::ObjectId ()
    : m_classId (0),
      m_instanceId (0)
{
}

ObjectId &ObjectId::operator = (const ObjectId &rhs)
{
    m_classId    = rhs.m_classId;
    m_instanceId = rhs.m_instanceId;

    return (*this);
}

bool ObjectId::operator == (const ObjectId &rhs) const
{
    if ((m_classId == rhs.m_classId) && (m_instanceId == rhs.m_instanceId))
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

bool ObjectId::operator != (const ObjectId &rhs) const
{
    return (!(operator == (rhs)));
}

bool ObjectId::operator < (const ObjectId &rhs) const
{
    if (rhs.m_classId > m_classId)
    {
        return (true);
    }
    else if (rhs.m_classId < m_classId)
    {
        return (false);
    }
    else
    {
        if (rhs.m_instanceId > m_instanceId)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}

bool ObjectId::operator > (const ObjectId &rhs) const
{
    if (rhs.m_classId < m_classId)
    {
        return (true);
    }
    else if (rhs.m_classId > m_classId)
    {
        return (false);
    }
    else
    {
        if (rhs.m_instanceId < m_instanceId)
        {
            return (true);
        }
        else
        {
            return (false);
        }
    }
}

UI32 ObjectId::getClassId () const
{
    return (m_classId);
}

void ObjectId::setClassId (const UI32 &classId)
{
    m_classId = classId;
}

void ObjectId::setInstanceId (const UI64 &instanceId)
{
    m_instanceId = instanceId;
}

UI64 ObjectId::getInstanceId () const
{
    return (m_instanceId);
}

string ObjectId::toString () const
{
    return (string ("") + m_classId + string (":") + m_instanceId);
}

}
