/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef OBJECTID_H
#define OBJECTID_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class ObjectId
{
    private :
    protected :
    public :
                  ObjectId      (UI32 classId, UI64 instanceId);
                  ObjectId      (const ObjectId &rhs);
                  ObjectId      ();
        ObjectId &operator =    (const ObjectId &rhs);
        bool      operator ==   (const ObjectId &rhs) const;
        bool      operator !=   (const ObjectId &rhs) const;
        bool      operator <    (const ObjectId &rhs) const;
        bool      operator >    (const ObjectId &rhs) const;
        UI32      getClassId    () const;
        void      setClassId    (const UI32 &classId);
        UI64      getInstanceId () const;
        void      setInstanceId (const UI64 &instanceId);
        string    toString      () const;

    // Now the data members

    private :
        UI32 m_classId;
        UI64 m_instanceId;

    protected :
    public :
        static ObjectId NullObjectId;
};

}

#endif // OBJECTID_H
